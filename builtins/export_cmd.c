#include "../minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		lstlast_env(*lst)->next = new;
	else
		*lst = new;
}

void ap_env(t_env **paths, char *res)
{   
    t_env *temp;
    char *env_new;

    env_new = ft_strdup(res);
    temp = malloc(sizeof(t_env));
    if(!temp)
        return ;
    temp->env = res;
    temp->next = NULL;
    ft_lstadd_back_env(paths,temp);
}

void export_cmd(char **str, t_path **paths)
{   
    t_env *tmp;
    char **sep;
    char *tmp_char;
    int   i;
    int checker;

    i = 1;
    if(!ft_strncmp("export",str[0],7) && str[1] == NULL)
        env_cmd(str, paths);
    else if(!ft_strncmp("export",str[0],7) && str[1] != NULL)
    {   
        while(str[i])
        {   
            sep = separator(str[i]);
            if(!sep)
                return ;
            tmp_char = ft_strjoin(sep[0],"=");
            tmp = (*paths)->env_struct;
            checker = 0;
            while(tmp)
            {
                if(!ft_strncmp(tmp_char,tmp->env,ft_strlen(tmp_char)))
                {   
                    free(tmp->env);
                    tmp->env = ft_strjoin(tmp_char,sep[1]);
                    (free_double(sep),free(tmp_char));
                    checker = 1;
                    break;
                }
                tmp = tmp->next;
            }
            if(!checker) 
                (ap_env(&(*paths)->env_struct,ft_strjoin(tmp_char,sep[1])),free_double(sep),free(tmp_char));
            i++;
        }
    }
    return ;
}
