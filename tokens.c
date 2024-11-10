#include "minishell.h"

t_tree *init_op_node(char op)
{
	t_tree *node;

	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_OPERATOR;
	node->data.operator = op;
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm'; 
	return (node);
}

t_tree *init_exp_node(char *str, int start, int end)
{
	t_tree *node;

	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_EXPRESSION;
	node->data.expression = ft_substr(str, start, end - start);
	if (!node->data.expression)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

t_tree *init_cmd_node(char *str, int end)
{
    t_tree *node;

    node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
    node->type = NODE_COMMAND;
    // node->data.command = remove_qoutes(str);
	node->data.command = ft_substr(str, 0, end);
	if (!node->data.command)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

t_tree *init_args_node(char *str, int start, int end)
{
	t_tree *node;

    node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
    node->type = NODE_ARGUMENT;
	node->data.argument = ft_substr(str, start, end);
	if (!node->data.argument)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}