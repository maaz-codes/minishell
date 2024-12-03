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

int	splitter(char **str, t_tree **node, int i, int j)
{
	if (split_operator(str, node, i, j))
		return (1);
	else if (!operator_ahead(*str, i) && split_redirection(str, node, i, j))
		return (1);
	else if (!redirection_ahead(*str, i) && !operator_ahead(*str, i)
		&& split_cmd(str, i, node))
		return (1);
	return (0);
}

t_tree	*tokenizer(char **str, t_tree **node)
{
	int	i;

	i = 0;
	while (i <= ft_strlen(*str))
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			i = inside_qoutes((*str)[i], *str, i);
			continue ;
		}
		if (splitter(str, node, i, 0))
			break ;
		i++;
	}
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

t_tree	*tokenization(char **str)
{
	t_tree	*tree;

	if (!qoutes_checker(*str))
		return (free_str(str), print_error(ERR_FORMAT), NULL);
	else
	{
		tree = NULL;
		if (!strip_spaces(str))
			return (free_str(str), print_exit(ERR_MALLOC), NULL);
		if (ft_strlen(*str) == 0)
			return (NULL);
		tokenizer(str, &tree);
		if (tree == NULL)
			return (NULL);
		else
		{
			tree->level = 0;
			if (!syntax_checker(tree))
				return (print_error(ERR_FORMAT), NULL); // free the tree...
			// print_tree(tree);
		}
	}
	return (tree);
}
