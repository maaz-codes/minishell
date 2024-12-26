/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:05:22 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/26 19:27:27 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_args(t_tree **arg_node, t_env *env, t_shl *shl)
{
	int	i;

	i = 0;
	while ((*arg_node)->data.args[i])
	{
		(*arg_node)->data.args[i] = env_expansion(
				(*arg_node)->data.args[i], env, shl);
		(*arg_node)->data.args[i] = remove_qoutes((*arg_node)->data.args[i]);
		i++;
	}
}

void	expansions(t_tree **tree, t_env *env, t_shl *shl)
{
	if ((*tree))
	{
		if ((*tree)->type == NODE_REDIR
			&& ft_strncmp((*tree)->data.redir, "<<", 2) == 0)
			(*tree)->right->type = NODE_LMTR;
		if ((*tree)->left != NULL)
			expansions(&(*tree)->left, env, shl);
		if ((*tree)->right != NULL)
			expansions(&(*tree)->right, env, shl);
		if ((*tree)->type == NODE_OP || (*tree)->type == NODE_LMTR)
			;
		else if ((*tree)->type == NODE_ARG)
			expand_args(tree, env, shl);
		else
			(*tree)->data.exp = env_expansion((*tree)->data.exp,
					env, shl);
	}
}
