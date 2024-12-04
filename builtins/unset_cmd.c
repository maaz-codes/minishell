#include "../minishell.h"

void free_nodes(t_env *tmp_env, t_exp *tmp_exp)
{
    free(tmp_env->env);
    free(tmp_env);
    free(tmp_exp->exp);
    free(tmp_exp);
}

void declare_struct(t_path **paths, t_env **tmp_env, t_exp **tmp_exp,int mode)
{   
    if(mode == 0)
    {
        *tmp_env = (*paths)->env_struct;
        *tmp_exp = (*paths)->exp_struct;
    }
    else if(mode == 1)
    {
        (*paths)->env_struct = (*tmp_env)->next;
        (*paths)->exp_struct = (*tmp_exp)->next;
    }
}

void iterate_nodes(t_env **pr_env, t_env **tmp_env, t_exp **pr_exp, t_exp **tmp_exp)
{   
    *pr_env = *tmp_env;
    *pr_exp = *tmp_exp;
    *tmp_env = (*tmp_env)->next;
    *tmp_exp = (*tmp_exp)->next;
}

void remove_node(t_path **paths,int pos)
{
    t_env *tmp_env;
    t_exp *tmp_exp;
    t_env *prev_env;
    t_exp *prev_exp;
    int i;

    i = 0;
    declare_struct(paths,&tmp_env,&tmp_exp,0);
    while(tmp_env && tmp_exp)
    {
        if(i == pos)
            break;
        i++;
        iterate_nodes(&prev_env,&tmp_env,&prev_exp,&tmp_exp);
    }
    if(tmp_env == NULL && tmp_exp == NULL)
        return ;
    if(prev_env != NULL && prev_exp != NULL)
    {
        prev_env->next = tmp_env->next;
        prev_exp->next = tmp_exp->next;
    }
    else 
        declare_struct(paths,&tmp_env,&tmp_exp,1);
    free_nodes(tmp_env,tmp_exp);   
}

void unset_cmd(char **str, t_path **paths)
{   
    t_env *tmp;
    int i;
    int pos;
    
    i = 1;
    if(str[1] == NULL)
    {
        printf("unset: not enough arguments\n");
        return ;
    }
    while(str[i])
    {   
        tmp = (*paths)->env_struct;
        pos = 0;
        while(tmp)
        {
            if(!ft_strncmp(str[i],tmp->env,ft_strlen(str[i])))
                break ;
            pos++;
            tmp = tmp->next;
        }
        remove_node(paths,pos);
        i++;
    }
}
