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
	if (node->type == NODE_ARGUMENT)
	{
		// printf("--freed:args\n");
		if(node->data.argument)
			free_array(node->data.argument);
	}
	else if (node->type == NODE_OPERATOR)
		return ;
	else
	{
		// printf("--freed:expression\n");
		if(node->data.expression)
		{
			// free(node->data.expression);
			node->data.expression = NULL;
		}	
		
	}
	// printf("--freed:(*node)\n");
	free(node);
}

void lumberjack(t_tree *tree)
{
	if (tree)
	{
		if (tree->left != NULL)
		{
			// printf("node: %s\n", tree->left->data.expression);
			lumberjack(tree->left);
		}
		if (tree->right != NULL)
		{
			// printf("node: %s\n", tree->right->data.expression);
			lumberjack(tree->right);
		}
		// free(tree->data.expression);
		// free(tree);
		chop_branch(tree);
	}
}