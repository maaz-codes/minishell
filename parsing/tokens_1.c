/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:09:28 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 17:14:28 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*init_log_op_node(char spl_op)
{
	t_tree	*node;

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

t_tree	*init_op_node(char op)
{
	t_tree	*node;

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

t_tree	*init_redir_node(char *redir)
{
	t_tree	*node;

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

t_tree	*init_file_node(char *str, int start, int end)
{
	t_tree	*node;

	if (*str == '\0')
		return (NULL);
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

t_tree	*init_exp_node(char **str)
{
	t_tree	*node;

	strip_spaces(str);
	if (ft_strlen(*str) == 0)
		return (free_str(str), NULL);
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
