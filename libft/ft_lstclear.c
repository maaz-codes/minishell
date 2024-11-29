#include "../minishell.h"

// void	ft_lstdelone(t_path **lst)
// {
// 	if (!(*lst))
// 		return ;
	
// 	free((*lst)->pwd);
// 	free((*lst)->pwd_old);
// 	free((*lst));
	
// }

void	ft_lstclear_path(t_path **lst)
{
	t_path	*node;
	
	if (!lst || !*lst)
		return ;
	while (*lst)
	{	
		node = (*lst)->next;
		free((*lst)->pwd);
		free((*lst)->pwd_old);
		free((*lst));
		*lst = node;
	}
}


void	ft_lstclear_env(t_env **lst)
{
	t_env	*node;
	
	if (!lst || !*lst)
		return ;
	while (*lst)
	{	
		node = (*lst)->next;
		free((*lst)->env);
		free((*lst));
		*lst = node;
	}
}

void	ft_lstclear_exp(t_exp **lst)
{
	t_exp	*node;
	
	if (!lst || !*lst)
		return ;
	while (*lst)
	{	
		node = (*lst)->next;
		free((*lst)->exp);
		free((*lst));
		*lst = node;
	}
}
