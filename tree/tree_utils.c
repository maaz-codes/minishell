/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:41:00 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/24 12:14:53 by maakhan          ###   ########.fr       */
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

// void	print_tree(t_tree *tree)
// {
// 	if (tree == NULL)
// 		return ;
// 	if (tree->left != NULL)
// 	{
// 		tree->left->level += tree->level;
// 		tree->left->pos = 'l';
// 		print_tree(tree->left);
// 	}
// 	if (tree->right != NULL)
// 	{
// 		tree->right->level += tree->level;
// 		tree->right->pos = 'r';
// 		print_tree(tree->right);
// 	}
// 	print_data(tree);
// }

// void	print_data(t_tree *tree)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < tree->level)
// 		printf("	");
// 	if (tree->type == NODE_EXP)
// 		printf("%c: %s type: exp\n", tree->pos, tree->data.exp);
// 	else if (tree->type == NODE_LOG_OP)
// 		printf("%c: %s type: log_op\n", tree->pos,
// 			tree->data.log_op);
// 	else if (tree->type == NODE_OP)
// 		printf("%c: %c type: operator\n", tree->pos, tree->data.op);
// 	else if (tree->type == NODE_REDIR)
// 		printf("%c: %s type: redir^\n", tree->pos, tree->data.redir);
// 	else if (tree->type == NODE_FILE)
// 		printf("%c: %s type: file\n", tree->pos, tree->data.file);
// 	else if (tree->type == NODE_HDOC)
// 		printf("%c: %d type: here_doc\n", tree->pos, tree->data.here_doc);
// 	else if (tree->type == NODE_LMTR)
// 		printf("%c: %s type: limiter\n", tree->pos, tree->data.file);
// 	else if (tree->type == NODE_CMD)
// 		printf("%c: %s type: cmd\n", tree->pos, tree->data.cmd);
// 	else if (tree->type == NODE_ARG)
// 	{
// 		printf("%c: ", tree->pos);
// 		i = -1;
// 		while (tree->data.args[++i])
// 			printf("%s, ", tree->data.args[i]);
// 		printf("type: args\n");
// 	}
// 	printf("\n");
// }
