/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:41:00 by maakhan           #+#    #+#             */
/*   Updated: 2025/01/13 19:15:27 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_array(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void	add_node(t_tree **tree, t_tree *node, int side)
{
	if (!node)
		return ;
	if (*tree == NULL)
	{
		*tree = node;
		return ;
	}
	if ((*tree)->left == NULL && side == LEFT)
		(*tree)->left = node;
	else if ((*tree)->right == NULL)
		(*tree)->right = node;
}
