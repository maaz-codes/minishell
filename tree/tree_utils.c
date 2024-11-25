#include "../minishell.h"

int count_array(char **array)
{
	int len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void add_node(t_tree **tree, t_tree *node, int side)
{
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

void print_data(t_tree *tree)
{
	int i = 0;
	while (i < tree->level)
	{
		printf("	");
		i++;
	}
	if (tree->type == NODE_EXPRESSION)
	{
		printf("%c: %s = type: %d\n", tree->pos, tree->data.expression, tree->type);
		// printf("data: %s		type: EXP pos: %c lvl: %d\n", tree->data.expression, tree->pos, tree->level);
	}
	else if (tree->type == NODE_LOG_OPERATOR)
	{
		printf("%c: %s = type: %d\n", tree->pos, tree->data.log_operator, tree->type);
		// printf("data: %s		type: EXP pos: %c lvl: %d\n", tree->data.expression, tree->pos, tree->level);
	}
	else if (tree->type == NODE_OPERATOR)
	{
		printf("%c: %c = type: %d\n", tree->pos, tree->data.operator, tree->type);
		// printf("data: %c			type: OPT{%d} pos: %c lvl: %d\n", tree->data.operator, tree->type, tree->pos, tree->level);
	}
	else if (tree->type == NODE_REDIRECTION)
	{
		printf("%c: %s = type: %d\n", tree->pos, tree->data.redirection, tree->type);
		// printf("data: %s			type: REDIR pos: %c lvl: %d\n", tree->data.redirection, tree->pos, tree->level);
	}
	else if (tree->type == NODE_COMMAND)
	{
		printf("%c: %s = type: %d\n", tree->pos, tree->data.command, tree->type);
		// printf("data: %s		type: CMD pos: %c lvl: %d\n", tree->data.command, tree->pos, tree->level);
	}
	else if (tree->type == NODE_ARGUMENT)
	{
		printf("%c: ", tree->pos);
		i = 0;
		while(tree->data.argument[i])
		{
			printf("%s, ", tree->data.argument[i]);
			i++;
		}
		printf(" = type: %d\n", tree->type);
		// printf("		type: ARGS pos: %c lvl: %d\n", tree->pos, tree->level);
	}
	printf("\n");
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