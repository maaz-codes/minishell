/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:08:29 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 17:08:37 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
