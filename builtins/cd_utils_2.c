#include "../minishell.h"

void ft_append(t_path **paths, char *res)
{   
    t_path *temp;
    char *old_path;
    char *new_path;

    old_path = ft_strdup(ft_lstlast_path(*paths)->pwd);
    new_path = ft_strdup(res);
    temp = malloc(sizeof(t_path));
    if(!temp)
        return ;
    temp->pwd = new_path;
    temp->pwd_old = old_path;
    temp->next = NULL;
    (add_NEWPWD(paths,temp),add_OLDPWD(paths,temp));
    add_OLDPWD_exp(paths,temp);
    ft_lstadd_back_path(paths,temp);
}

void append_switch_struct(t_path **paths, t_path **temp)
{   
    *temp = malloc(sizeof(t_path));
    if(!temp)
        return ;
    (*temp)->pwd = ft_strdup(ft_lstlast_path(*paths)->pwd_old);
    (*temp)->pwd_old = ft_strdup(ft_lstlast_path(*paths)->pwd);
    (*temp)->next = NULL;
}

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
