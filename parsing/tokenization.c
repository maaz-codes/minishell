#include "../minishell.h"

int	strip_spaces(char **str)
{
	char	*striped;
	char	*original;

	if (*str == NULL)
		return (1);
	striped = ft_strtrim(*str, " ");
	if (!striped)
		print_exit(ERR_MALLOC);
	original = *str;
	*str = striped;
	free(original);
	return (1);
}

int	splitter(char *str, t_tree **node, int i, int j)
{
	if (split_log_operator(str, node, i, j))
		return (1);
	else if (!spl_operator_ahead(str, i) && split_operator(str, node, i, j))
		return (1);
	else if (!operator_ahead(str, i) && !spl_operator_ahead(str, i)
		&& split_redirection(str, node, i, j))
		return (1);
	else if (!redirection_ahead(str, i) && !operator_ahead(str, i)
		&& !spl_operator_ahead(str, i) && split_cmd(str, i, node))
		return (1);
	return (0);
}

t_tree	*tokenizer(char *str, t_tree **node)
{
	int	i;
	int	j;

	i = 0;
	j = i;
	if (!strip_spaces(&str))
		return (print_error(ERR_MALLOC), NULL);
	while (i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			continue ;
		}
		if (splitter(str, node, i, j))
			break ;
		i++;
	}
	free(str);
	return (*node);
}

int	check_syntax(t_tree *node, t_tree *parent)
{
	if (node->type == NODE_LOG_OPERATOR)
		return (check_log_op_node(node));
	else if (node->type == NODE_OPERATOR)
		return (check_op_node(node));
	else if (node->type == NODE_REDIRECTION)
		return (check_redir_node(node));
	return (1);
}

t_tree	*tokenization(char *str)
{
	t_tree	*tree;

	if (!qoutes_checker(str))
		return (print_error(ERR_FORMAT), NULL);
	else
	{
		tree = NULL;
		tokenizer(str, &tree);
		if (tree == NULL)
			print_error(ERR_FORMAT);
		else
		{
			tree->level = 0;
			if (!syntax_checker(tree))
			{
				print_error(ERR_FORMAT);
				return (NULL);
			}
			// print_tree(tree);
		}
	}
	return (tree);
}
