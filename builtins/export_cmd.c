#include "../minishell.h"

void export_cmd(char **str, t_path **paths)
{   
    t_env *tmp;
    t_env *new_env;
    char **sep;
    char *tmp_char;
    int   i;
    int checker;

    i = 1;
    tmp = (*paths)->env_struct;
    new_env = malloc(sizeof(t_env));
    
    if(!ft_strncmp("export",str[0],7) && str[1] == NULL)
        env_cmd(str, paths);
    if(!ft_strncmp("export",str[0],7) && str[1] != NULL)
    {
        while(str[i])
        {   
            sep = ft_split(str[i],'=');
            tmp_char = ft_strjoin(sep[0],"=");
            tmp = (*paths)->env_struct;
            checker = 0;
            while(tmp)
            {
                if(!ft_strncmp(tmp_char,tmp->env,ft_strlen(tmp_char)))
                {
                    free(tmp->env);
                    tmp->env = ft_strdup(str[i]);
                    free(tmp_char);
                    free_double(sep);
                    checker = 1;
                    return ;
                }
                tmp = tmp->next;
            }
            if(!checker)
            {
                new_env->env = ft_strdup(str[i]);
                new_env->next = NULL;
                lstlast_env((*paths)->env_struct)->next = new_env;
                free(tmp_char);
                free_double(sep);
            }
            i++;
        }
    }
    return ;
}
