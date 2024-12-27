/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:13:40 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/27 17:08:25 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strip_spaces(char **str)
{
	char	*striped;
	char	*original;

	if (*str == NULL)
		return (1);
	striped = ft_strtrim(*str, " ");
	if (!striped)
		return (print_error(ERR_MALLOC));
	original = *str;
	*str = striped;
	free(original);
	return (1);
}

int	splitter(char *str, t_tree **node, int i)
{
	if (split_operator(str, node, i))
		return (1);
	else if (!operator_ahead(str, i) && split_redirection(str, node, i))
		return (1);
	else if (!redirection_ahead(str, i) && !operator_ahead(str, i)
		&& split_cmd(str, i, node))
		return (1);
	return (0);
}

t_tree	*tokenizer(char *str, t_tree **node)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			continue ;
		}
		if (splitter(str, node, i))
			break ;
		i++;
	}
	return (*node);
}

int	check_syntax(t_tree *node)
{
	if (node->type == NODE_LOG_OP)
		return (check_log_op_node(node));
	else if (node->type == NODE_OP)
		return (check_op_node(node));
	else if (node->type == NODE_REDIR)
		return (check_redir_node(node));
	return (1);
}

t_tree	*tokenization(char *str, t_shl *shl)
{
	t_tree	*tree;

	tree = NULL;
	if (!qoutes_checker(str))
		return (free(str), print_error(ERR_FORMAT), NULL);
	else
	{
		tree = NULL;
		if (!strip_spaces(&str))
			(free(str), free_array(shl->env),
				nuke(shl, TNT), exit(EXIT_FAILURE));
		if (ft_strlen(str) == 0)
			return (free(str), NULL);
		shl->head = tokenizer(str, &tree);
		if (tree == NULL)
			return (NULL);
		else
		{
			tree->level = 0;
			if (!syntax_checker(tree))
				return (nuke(shl, 0), print_error(ERR_FORMAT), NULL);
		}
	}
	return (tree);
}
