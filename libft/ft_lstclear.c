#include "../minishell.h"

void	ft_lstdelone(t_path **lst)
{
	if (!(*lst))
		return ;
	
	free((*lst)->pwd);
	free((*lst)->pwd_old);
	free((*lst));
	
}

void	ft_lstclear(t_path **lst)
{
	t_path	*node;
	
	if (!lst || !*lst)
		return ;
	while (*lst)
	{	
		node = (*lst)->next;
		ft_lstdelone(lst);
		*lst = node;
	}
}
