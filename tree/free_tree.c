/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:06:11 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/20 17:18:12 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_array(char **array)
{
	int i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
}

void free_node(t_tree *node)
{
	if (node->type == NODE_ARGUMENT)
		free_array(node->data.argument);
	else if (node->type == NODE_OPERATOR)
		;
	else
		free(node->data.expression);
	free(node);
}

void free_tree(t_tree *tree)
{
	if (tree)
	{
		if (tree->left)
			free_tree(tree->left);
		else if (tree->right)
			free_tree(tree->right);
		free_node(tree);
	}
}