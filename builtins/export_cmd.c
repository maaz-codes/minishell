#include "../minishell.h"

char **separator(char *str)
{
    int len;
    char **sep;
    char *holder;
    char **res;
    int check;

    sep = ft_split(str,'=');
    len = 0;
    check = 1;
    while(str[len] != '=' && str[len])
        len++;
    if(ft_strlen(str) == len)
        check = 0;
    holder = malloc(sizeof(char *) * len + 1);
    res = (char **)malloc(sizeof(char *) * 3);
    if(!holder || !res)
        return (NULL);
    if(!check)
        ft_strlcpy(holder,str,ft_strlen(holder));
    else
        ft_strlcpy(holder,str + (len + 1),ft_strlen(holder) - (len - 1));
    res[0] = ft_strdup(sep[0]);
    res[1] = holder;
    res[2] = NULL;
    free_double(sep);
    return(res);
}

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
    t_env *new_env;
    char **sep;
    char *tmp_char;
    int   i;
    int checker;
    t_env *tmp_env_holder;

    i = 1;
    new_env = malloc(sizeof(t_env));
    if(!ft_strncmp("export",str[0],7) && str[1] == NULL)
        env_cmd(str, paths);
    else if(!ft_strncmp("export",str[0],7) && str[1] != NULL)
    {   
        while(str[i])
        {   
            sep = separator(str[i]);
            tmp_char = ft_strjoin(sep[0],"=");
            tmp = (*paths)->env_struct;
            checker = 0;
            while(tmp)
            {
                if(!ft_strncmp(tmp_char,tmp->env,ft_strlen(tmp_char)))
                {   
                    printf("enter here\n");
                    free(tmp->env);
                    tmp->env = ft_strjoin(tmp_char,sep[1]);
                    free_double(sep);
                    checker = 1;
                    break;
                }
                tmp = tmp->next;
            }
            if(!checker) 
                (ap_env(&new_env,ft_strjoin(tmp_char,sep[1])),free_double(sep));
            i++;
        }
        if(new_env)
            lstlast_env((*paths)->env_struct)->next = new_env;
    }
    return ;
}
