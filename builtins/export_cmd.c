#include "../minishell.h"

void ap_env(t_env **env, char *res)
{   
    t_env *temp;
    char *env_new;

    env_new = ft_strdup(res);
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

    i = 0;
    check = 1;
    tmp = (*paths)->exp_struct;
    while(str[i] != '=' && str[i])
        i++;
    if(i == ft_strlen(str))
        check = 0;
    while(tmp)
    {
        if(!ft_strncmp(tmp_char,tmp->exp,ft_strlen(tmp_char)))
        {   
            free(tmp->exp);
            tmp->exp = ft_strjoin(tmp_char,sep);
            return ;
        }
        tmp = tmp->next;
    }
    if(!check)
        ap_exp(&(*paths)->exp_struct,ft_strdup(str));
    else
        ap_exp(&(*paths)->exp_struct,ft_strjoin(tmp_char,sep));
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
            export_t_env(paths,tmp_char,sep[1],str[i]);
            export_t_exp(paths,tmp_char,sep[1],str[i]);
            (free_double(sep),free(tmp_char));
            i++;
        }
    }
    return ;
}
