#include "../minishell.h"

t_path	*ft_lstlast_path(t_path *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_env	*lstlast_env(t_env *lst)
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
    t_env *old_pwd;

    path_name = ft_strdup("OLDPWD=");
    tmp = (*paths)->env_struct;
    old_pwd = malloc(sizeof(t_env));
    while(tmp)
    {
        if(!ft_strncmp(tmp->env,"OLDPWD=",7))
        {   
            free(tmp->env);
            tmp->env = ft_strjoin(path_name,new->pwd_old);
            free(path_name);
            free(old_pwd);
            return ;
        }
        tmp = tmp->next;
    }
    old_pwd->env = ft_strjoin(path_name,new->pwd_old);
    old_pwd->next = NULL;
    lstlast_env((*paths)->env_struct)->next = old_pwd;
    free(path_name);
    return ;
}
