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

	if (!redir)
		print_exit(ERR_MALLOC);
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
	// if (*str == '\0')
	// 	return (NULL);
	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_EXPRESSION;
	node->data.expression = *str;
	if (!node->data.expression)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

t_tree *init_cmd_node(char *cmd_tmp)
{
    t_tree *node;

    node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
    node->type = NODE_COMMAND;
	node->data.command = remove_qoutes(cmd_tmp);
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

t_tree *init_args_node(char *args, char *cmd)
{
	t_tree *node;

    node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
    node->type = NODE_ARGUMENT;
	strip_spaces(&args);
	node->data.argument = split_args(args, cmd);
	free(args);
	if (!node->data.argument)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}


// char *exp_after_redir_node(char *str, int start, int end, int append)
// {
// 	char *exp;
// 	int first_half;
// 	int second_half;

// 	first_half = start;
// 	second_half = end - append;
// 	while (str[end] == ' ')
// 		end++;
// 	while (end < ft_strlen(str))
// 	{
// 		if (str[end] == '"' || str[end] == '\'')
// 		{
// 			end = inside_qoutes(str[end], str, end);
// 			continue ;
// 		}
// 		if (str[end] == ' ')
// 			break ;
// 		end++;
// 	}
// 	char *cmd_name = ft_substr(str, first_half, second_half - first_half);
// 	if (*cmd_name == '\0')
// 		return (NULL);
// 	char *cmd_flags = ft_substr(str, end, ft_strlen(str));
// 	if (!cmd_flags || !cmd_name)
// 		print_exit(ERR_MALLOC);
// 	exp = ft_strjoin(cmd_name, cmd_flags);
// 	if (!exp)
// 		print_exit(ERR_MALLOC);
// 	return (exp);
// }

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
		print_exit(ERR_MALLOC);
	left_exp = ft_strjoin(first_half, second_half);
	if (!left_exp)
		print_exit(ERR_MALLOC);
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
	if (*file_name == '\0')
		return (NULL);
	return (file_name);
}
