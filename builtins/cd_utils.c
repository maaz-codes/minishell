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