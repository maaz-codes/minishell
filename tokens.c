#include "minishell.h"

t_tree *init_op_node(char op)
{
	t_tree *node;

	node = malloc(sizeof(t_tree));
	node->type = NODE_OPERATOR;
	node->t_data.operator = op;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree *init_exp_node(char *str, int start, int end)
{
	t_tree *node;

	node = malloc(sizeof(t_tree));
	node->type = NODE_EXPRESSION;
	node->t_data.expression = ft_substr(str, start, end - start);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree *init_cmd_node(char *str)
{
    t_tree *node;

    node = malloc(sizeof(t_tree));
    node->type = NODE_COMMAND;
    node->t_data.command = remove_qoutes(str);
	return (node);
}