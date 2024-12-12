/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lumberjack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:06:11 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/30 09:52:57 by maakhan          ###   ########.fr       */
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
	free(array);
}

void chop_branch(t_tree *node)
{
	if (!node)
		return ;
	if (node->type == NODE_HEREDOC || node->type == NODE_OPERATOR)
		;
	else if (node->type == NODE_ARGUMENT)
		free_array(node->data.argument);
	else
		free(node->data.expression);
	free(node);
}

t_tree *lumberjack(t_tree *tree)
{
	if (tree == NULL)
		return (NULL);
	if (tree->left != NULL)
		lumberjack(tree->left);
	if (tree->right != NULL)
		lumberjack(tree->right);
	chop_branch(tree);
	return (NULL);
}