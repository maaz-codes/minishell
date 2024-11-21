#include "../minishell.h"

t_path	*ft_lstlast_path(t_path *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_path(t_path **lst, t_path *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast_path(*lst)->next = new;
	else
		*lst = new;
}

void add_NEWPWD(t_path **paths, t_path *new)
{   
    t_env *tmp;
    char *path_name;

    path_name = ft_strdup("PWD=");
    tmp = (*paths)->env_struct;
    while(tmp)
    {   
        if(!ft_strncmp(tmp->env,"PWD=",4))
        {   
            free(tmp->env);
            tmp->env = ft_strjoin(path_name,new->pwd);
            free(path_name);
            return ;
        }
        tmp = tmp->next;
    }
    return ;
}

void add_OLDPWD(t_path **paths, t_path *new)
{
    t_env *tmp;
    char *path_name;

    path_name = ft_strdup("OLDPWD=");
    tmp = (*paths)->env_struct;
    while(tmp)
    {
        if(!ft_strncmp(tmp->env,"OLDPWD=",4))
        {   
            free(tmp->env);
            tmp->env = ft_strjoin(path_name,new->pwd_old);
            free(path_name);
            return ;
        }
        tmp = tmp->next;
    }
    tmp->env = ft_strjoin(path_name,new->pwd_old);
    tmp->next = NULL;
    free(path_name);
    return ;
}
