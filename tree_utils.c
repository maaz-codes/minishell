#include "minishell.h"

void add_node(t_tree **tree, t_tree *node)
{
	if (*tree == NULL)
	{
		*tree = node;
		return ;
	}
	if ((*tree)->left == NULL)
		(*tree)->left = node;
	else if ((*tree)->right == NULL)
		(*tree)->right = node;
}

void print_data(t_tree *tree)
{
	if (tree->type == NODE_EXPRESSION)
		printf("data: %s type: %d\n", tree->t_data.expression, tree->type);
	else if (tree->type == NODE_OPERATOR)
		printf("data: %c type: %d\n", tree->t_data.operator, tree->type);
}

void print_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
	{
		printf("left:");
		print_tree(tree->left);
		if (tree->right != NULL)
		{
			printf("right:");
			print_tree(tree->right);
		}
		else
			print_data(tree);
	}
	print_data(tree);
}