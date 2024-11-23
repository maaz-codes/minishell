#include "../minishell.h"

void strip_spaces(char **str)
{
	char *striped;
	char *original;

	if (*str == NULL)
		return ;
	striped = ft_strtrim(*str, " ");
	if (!striped)
		print_exit(ERR_MALLOC);
	original = *str;
	*str  = striped;
	free(original);
}

int splitter(char *str, t_tree **node, int i, int j)
{
	if (split_log_operator(str, node, i, j))
		return (1);
	else if (!spl_operator_ahead(str, i) && split_operator(str, node, i, j))
		return (1);
	else if (!operator_ahead(str, i) && !spl_operator_ahead(str, i) && split_redirection(str, node, i, j))
		return (1);
	else if (!redirection_ahead(str, i) && !operator_ahead(str, i) && !spl_operator_ahead(str, i) && split_cmd(str, &i, node))
		return (1);
	return (0);
}

t_tree *tokenizer(char *str, t_tree **node)
{
	int	i;
	int j;
	int	qoutes;

	qoutes = 0;
	i = 0;
	j = i;
	// printf("exp: -%s-\n", str);
	strip_spaces(&str);
	while (i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
			inside_qoutes(&qoutes, symbol_checker(str[i]), str, &i);
		if (str[i] == '"' || str[i] == '\'')
			continue ;
		if (splitter(str, node, i , j))
			break ;
		i++;
	}
	return (*node);
}

int check_syntax(t_tree *node, t_tree *parent)
{
	if (node->type == NODE_LOG_OPERATOR)
		return (check_log_op_node(node));
	else  if (node->type == NODE_OPERATOR)
		return (check_op_node(node));
	else if (node->type == NODE_REDIRECTION)
		return (check_redir_node(node, parent));
	// else if (node->type == NODE_COMMAND)
	// 	check_cmd_node(node);
	return (1);
}

// int syntax_error(t_tree *tree)
// {
// 	if (tree == NULL)
// 		return (0);
// 	if (tree->left != NULL)
// 	{
// 		if (!syntax_error(tree->left))
// 			return (0);
// 		if (tree->right != NULL)
// 		{
// 			if (!syntax_error(tree->right))
// 				return (0);
// 		}
// 		else
// 		{
// 			if (!check_syntax(tree))
// 				return (0);
// 		}
// 	}
// 	if (!check_syntax(tree))
// 		return (0);
// 	return (1);
// }	

t_tree *tokenization(char *str)
{
	t_tree *tree;

	strip_spaces(&str);
	if (*str == '\0')
		return (NULL);
	if (!qoutes_checker(str))
		print_error(ERR_FORMAT);
	else
	{
		tree = NULL;
		tokenizer(str, &tree);
		if (tree == NULL)
			print_error(ERR_FORMAT);
		else
		{
			tree->level = 0;
			// print_tree(tree);
		}
		// if (!syntax_error(tree))
		// {
		// 	// free_tree(tree);
		// 	print_error(ERR_FORMAT);
		// }
		// free_tree(tree);
	}
	return (tree);
}
