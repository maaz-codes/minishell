/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lumberjack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:42:01 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/26 16:01:34 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	nuke(t_shl *shl, int flag)
{
	close_last_fd(shl->head);
	if (flag == TNT)
	{
		ft_lstclear_env(&shl->paths->env_struct);
		ft_lstclear_exp(&shl->paths->exp_struct);
		ft_lstclear_path(&shl->paths);
	}
	lumberjack(shl->head);
	close(shl->std_fds.std_in);
	close(shl->std_fds.std_out);
	close(shl->std_fds.std_err);
	if (flag == TNT)
		free(shl);
}

void	free_array(char **array)
{
	int	i;

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

void	chop_branch(t_tree *node)
{
	if (!node)
		return ;
	if (node->type == NODE_HDOC || node->type == NODE_OP)
		;
	else if (node->type == NODE_ARG)
		free_array(node->data.args);
	else
		free(node->data.exp);
	free(node);
}

t_tree	*lumberjack(t_tree *tree)
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

void	close_last_fd(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == NODE_HDOC)
		close(tree->data.here_doc);
	if (tree->left != NULL)
		close_last_fd(tree->left);
	if (tree->right != NULL)
		close_last_fd(tree->right);
}
