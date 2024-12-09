#include "../minishell.h"

void ap_env(t_env **env, char *res)
{   
    t_env *temp;
    char *env_new;

    env_new = res;
    temp = malloc(sizeof(t_env));
    if(!temp)
        return ;
    temp->env = res;
    temp->next = NULL;
    if (*env)
		lstlast_env(*env)->next = temp;
	else
		*env = temp;
}

void export_t_env(t_path **paths, char *tmp_char, char *sep, char *str)
{
    t_env *tmp;
    int i;

    i = 0;
    tmp = (*paths)->env_struct;
    while(str[i] != '=' && str[i])
        i++;
    if(i == ft_strlen(str))
        return ;
    while(tmp)
    {
        if(!ft_strncmp(tmp_char,tmp->env,ft_strlen(tmp_char)))
        {   
            free(tmp->env);
            tmp->env = ft_strjoin(tmp_char,sep);
            return ;
        }
        tmp = tmp->next;
    }
    (ap_env(&(*paths)->env_struct,ft_strjoin(tmp_char,sep)));
}

void export_t_exp(t_path **paths, char *tmp_char, char *sep, char *str)
{
    t_exp *tmp;
    int i;
    int check;
    char *joined_str;
    char *only_str;

    i = 0;
    check = 1;
    tmp = (*paths)->exp_struct;
    while(str[i] != '=' && str[i])
        i++;
    if(i == ft_strlen(str))
        check = 0;
    joined_str = ft_strjoin(tmp_char,sep);
    only_str = ft_strdup(str);
    while(tmp)
    {
        if(!ft_strncmp(tmp_char,tmp->exp,ft_strlen(tmp_char)))
        {   
            free(tmp->exp);
            tmp->exp = joined_str;
            free(only_str);
            return ;
        }
        tmp = tmp->next;
    }
    if(!check)
        ap_exp(&(*paths)->exp_struct,only_str);
    else
        ap_exp(&(*paths)->exp_struct,joined_str);
    (free(joined_str),free(only_str));
}

t_exp *int_exp(char **env)
{
    t_exp *node_new;
    int i;

    i = 1;
    if(!env)
        return (NULL);
    node_new = (t_exp *)malloc(sizeof(t_exp));
    if(node_new == NULL)
        return (NULL);
    node_new->exp = ft_strdup(env[0]);
    node_new->next = NULL;
    while(env[i])
        ap_exp(&node_new,env[i++]);
    return(node_new);
}

void export_cmd(char **str, t_path **paths)
{   
    t_env *tmp;
    char **sep;
    char *tmp_char;
    int   i;

    i = 1;
    if(!ft_strncmp("export",str[0],7) && str[1] == NULL)
        exp_print(paths);
        
    else if(!ft_strncmp("export",str[0],7) && str[1] != NULL)
    {   
        while(str[i])
        {   
            sep = separator(str[i]);
            if(!sep)
                return ;
            tmp_char = ft_strjoin(sep[0],"=");
            export_t_exp(paths,tmp_char,sep[1],str[i]);
            export_t_env(paths,tmp_char,sep[1],str[i]);
            (free_array(sep),free(tmp_char));
            i++;
        }
    }
    return ;
}
