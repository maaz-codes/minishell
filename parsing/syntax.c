/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:27:26 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 17:15:10 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_log_op_node(t_tree *node)
{
	if ((*node->left->data.expression) && (*node->right->data.expression))
		return (1);
	return (0);
}

int	check_op_node(t_tree *node)
{
	if (node->left != NULL && node->right != NULL)
	{
		if (!ft_strncmp(node->left->data.expression, "|", 2))
			return (0);
		return (1);
	}
	return (0);
}

int	check_redir_node(t_tree *node)
{
	if (!ft_strncmp(node->data.expression, "><", 2))
		return (0);
	if (!ft_strncmp(node->data.expression, "<>", 2))
		return (0);
	if (node->right != NULL)
	{
		if (!ft_strncmp(node->right->data.expression, "<", 2))
			return (0);
		else if (!ft_strncmp(node->right->data.expression, ">", 2))
			return (0);
		else if (!ft_strncmp(node->right->data.expression, "<<", 3))
			return (0);
		else if (!ft_strncmp(node->right->data.expression, ">>", 3))
			return (0);
		else if (!ft_strncmp(node->right->data.expression, "<>", 3))
			return (0);
		else if (!ft_strncmp(node->right->data.expression, "><", 3))
			return (0);
		else if (!ft_strncmp(node->right->data.expression, "|", 2))
			return (0);
		return (1);
	}
	return (0);
}

int	syntax_checker(t_tree *tree)
{
	if (tree->left != NULL)
		if (!syntax_checker(tree->left))
			return (0);
	if (tree->right != NULL)
		if (!syntax_checker(tree->right))
			return (0);
	if (tree->type == NODE_REDIRECTION)
		return (check_redir_node(tree));
	else if (tree->type == NODE_OPERATOR)
		return (check_op_node(tree));
	else
		return (1);
}
