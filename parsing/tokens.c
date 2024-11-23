#include "../minishell.h"

t_tree *init_log_op_node(char spl_op)
{
	t_tree *node;

	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_LOG_OPERATOR;
	if (spl_op == '&')
		node->data.log_operator = ft_strdup("&&");
	else if (spl_op == '|')
		node->data.log_operator = ft_strdup("||");
	if (node->data.log_operator == NULL)
		print_exit(ERR_MALLOC);
	return (node);
}

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

t_tree *init_redir_node(char *redir)
{
	t_tree *node;

	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_REDIRECTION;
	node->data.redirection = redir;
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm'; 
	return (node);
}

t_tree *init_file_node(char *str, int start, int end)
{
    t_tree *node;
	char *striped_str;

	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_FILE;
	striped_str = ft_substr(str, start, end - start);
	if (!striped_str)
		print_exit(ERR_MALLOC);
	strip_spaces(&striped_str);
	node->data.file = striped_str;
	if (!node->data.file)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

t_tree *init_exp_node(char *str, int start, int end)
{
	t_tree *node;
	char *striped_str;

	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_EXPRESSION;
	striped_str = ft_substr(str, start, end - start);
	if (!striped_str)
		print_exit(ERR_MALLOC);
	strip_spaces(&striped_str);
	node->data.expression = striped_str;
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
	node->data.command = remove_qoutes(ft_substr(str, 0, end));
	if (!node->data.command)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

// t_tree *init_node(char *str, int type)
// {
// 	t_tree *node;

//     node = malloc(sizeof(t_tree));
// 	if (!node)
// 		print_exit(ERR_MALLOC);
//     node->type = type;
// 	node->data.command = remove_qoutes(str);
// 	if (!node->data.command)
// 		print_exit(ERR_MALLOC);
// 	node->left = NULL;
// 	node->right = NULL;
// 	node->level = 1;
// 	node->pos = 'm';
// 	return (node);
// }

t_tree *init_args_node(char *str, int start, int end, char *cmd)
{
	t_tree *node;
	char *striped_str;

    node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
    node->type = NODE_ARGUMENT;
	striped_str = ft_substr(str, start, end);
	if (!striped_str)
		print_exit(ERR_MALLOC);
	strip_spaces(&striped_str);
	node->data.argument = split_args(striped_str, cmd);
	if (!node->data.argument)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}


char *exp_after_redir_node(char *str, int start, int end, int append)
{
	char *exp;
	int first_half;
	int second_half;
	int qoutes;

	first_half = start;
	second_half = end - append;
	qoutes = 0;
	while (str[end] == ' ')
		end++;
	while (end < ft_strlen(str))
	{
		if (str[end] == '"' || str[end] == '\'')
			inside_qoutes(&qoutes, symbol_checker(str[end]), str, &end);
		if (str[end] == '"' || str[end] == '\'')
			continue ;
		if (str[end] == ' ')
			break ;
		end++;
	}
	exp = ft_strjoin(ft_substr(str, first_half, second_half - first_half), ft_substr(str, end, ft_strlen(str)));
	if (!exp)
		print_exit(ERR_MALLOC);
	return (exp);
}

char *extract_file_name(char *str, int start, int end)
{
	int qoutes;
	int store_start;
	char *file_name;

	qoutes = 0;
	store_start = start;
	while (str[start] == ' ')
		start++;
	while (start < ft_strlen(str))
	{
		if (str[start] == '"' || str[start] == '\'')
			inside_qoutes(&qoutes, symbol_checker(str[start]), str, &start);
		if (str[start] == '"' || str[start] == '\'')
			continue ;
		if (str[start] == ' ')
			break ;
		start++;
	}
	file_name = ft_substr(str, store_start, start - store_start);
	if (!file_name)
		print_exit(ERR_MALLOC);
	return (file_name);
}
