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
		printf("data: %s		type: EXP pos: %c lvl: %d\n", tree->data.expression, tree->pos, tree->level);
	else if (tree->type == NODE_OPERATOR)
		printf("data: %c			type: OPT pos: %c lvl: %d\n", tree->data.operator, tree->pos, tree->level);
	else if (tree->type == NODE_COMMAND)
		printf("data: %s		type: CMD pos: %c lvl: %d\n", tree->data.command, tree->pos, tree->level);
	else if (tree->type == NODE_ARGUMENT)
		printf("data: %s		type: ARGS pos: %c lvl: %d\n", tree->data.argument, tree->pos, tree->level);
}

void print_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
	{
		tree->left->level += tree->level;
		tree->left->pos = 'l';
		print_tree(tree->left);
		if (tree->right != NULL)
		{
			tree->right->level += tree->level;
			tree->right->pos = 'r';
			print_tree(tree->right);
		}
		else
		{
			print_data(tree);
			return ;
		}
	}
	print_data(tree);
}