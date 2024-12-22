/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:05:22 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 17:06:51 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_args(t_tree **arg_node, t_env *env)
{
	int	i;

	i = 0;
	while ((*arg_node)->data.argument[i])
	{
		(*arg_node)->data.argument[i] = env_expansion(
				(*arg_node)->data.argument[i], env);
		i++;
	}
}

void	expansions(t_tree **tree, t_env *env)
{
	if ((*tree))
	{
		if ((*tree)->type == NODE_REDIRECTION
			&& ft_strncmp((*tree)->data.redirection, "<<", 2) == 0)
			(*tree)->right->type = NODE_LIMITER;
		if ((*tree)->left != NULL)
			expansions(&(*tree)->left, env);
		if ((*tree)->right != NULL)
			expansions(&(*tree)->right, env);
		if ((*tree)->type == NODE_OPERATOR || (*tree)->type == NODE_LIMITER)
			;
		else if ((*tree)->type == NODE_ARGUMENT)
			expand_args(tree, env);
		else
			(*tree)->data.expression = env_expansion((*tree)->data.expression,
					env);
	}
}
