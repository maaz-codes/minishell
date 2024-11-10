#include "../minishell.h"

void	ft_lstdelone(t_path *lst)
{
	if (!lst)
		return ;
	if (lst)
	{
		free(lst->pwd);
        // free(lst->old_pwd);
		free(lst);
	}
}

void	ft_lstclear(t_path **lst)
{
	t_path	*node;

	node = *lst;
	if (!lst || !*lst)
		return ;
	while (lst && *lst)
	{
		node = node->next;
		ft_lstdelone(*lst);
		*lst = node;
	}
}
