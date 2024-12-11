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
		return (print_error(ERR_MALLOC), NULL);
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

	if (!redir)
		print_exit(ERR_MALLOC);
	node = malloc(sizeof(t_tree));
	if (!node)
		(free(redir), print_exit(ERR_MALLOC));
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
	// char *striped_str;

	// striped_str = ft_substr(str, start, end - start);
	// if (!striped_str)
	// 	print_exit(ERR_MALLOC);
	strip_spaces(&str);
	if (*str == '\0')
		return (NULL);
	// printf("file: %s\n", striped_str);
	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_FILE;
	node->data.file = str;
	if (!node->data.file)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

t_tree *init_exp_node(char **str)
{
	t_tree *node;

	strip_spaces(str);
	if (ft_strlen(*str) == 0)
		return (free(*str), NULL);
	node = malloc(sizeof(t_tree));
	if (!node)
		(free(*str), print_exit(ERR_MALLOC));
	node->type = NODE_EXPRESSION;
	node->data.expression = *str;
	if (!node->data.expression)
		(free(*str), print_exit(ERR_MALLOC));
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

t_tree *init_cmd_node(char **cmd)
{
    t_tree *node;

    node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
    node->type = NODE_COMMAND;
	*cmd = remove_qoutes(*cmd);
	node->data.command = *cmd;
	if (!node->data.command)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	// free_array(cmd);
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

t_tree *init_args_node(char **args, char *cmd)
{
	t_tree *node;
	char **arguments;

    node = malloc(sizeof(t_tree));
	if (!node)
		(free(cmd), free(*args), print_exit(ERR_MALLOC));
    node->type = NODE_ARGUMENT;
	strip_spaces(args);
	arguments = split_args(*args, cmd);
	if (!arguments)
		(free(cmd), free(*args), print_exit(ERR_MALLOC));
	// free_array(args);
	node->data.argument = arguments;
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	// free_array(arguments);
	return (node);
}

char *exp_after_redir_node(char *str, char *first_half, int start)
{
	char *second_half;
	char *left_exp;

	while (str[start] == ' ') // reach to the first char of file_name
		start++;
	while (str[start])
	{
		if (str[start] == '"' || str[start] == '\'')
		{
			start = inside_qoutes(str[start], str, start);
			continue ;
		}
		if (str[start] == ' ')
			break ;
		start++;
	}
	second_half = ft_substr(str, start, ft_strlen(str));
	if (!second_half)
		(free(str), print_exit(ERR_MALLOC));
	left_exp = ft_strjoin(first_half, second_half);
	free(second_half);
	if (!left_exp)
		(free(str), print_exit(ERR_MALLOC));
	return (left_exp);
}

char *extract_file_name(char *str, int start, int end)
{
	int store_start;
	char *file_name;

	store_start = start;
	while (str[start] == ' ')
		start++;
	while (start < ft_strlen(str))
	{
		if (str[start] == '"' || str[start] == '\'')
		{
			start = inside_qoutes(str[start], str, start);
			continue ;
		}
		if (str[start] == ' ')
			break ;
		start++;
	}
	file_name = ft_substr(str, store_start, start - store_start);
	if (!file_name)
		print_exit(ERR_MALLOC);
	if (ft_strlen(file_name) == 0)
		return (free(file_name), NULL);
	return (file_name);
}
