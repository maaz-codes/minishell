/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:27:26 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/18 16:07:45 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_log_op_node(t_tree *node)
{
    if ((*node->left->data.expression) && (*node->right->data.expression))
        return (1);
    return (0);
}

int check_op_node(t_tree *node)
{
    if ((*node->left->data.expression) && (*node->right->data.expression))
        return (1);
    return (0);
}

int check_redir_node(t_tree *node, t_tree *parent)
{
    if ((*node->right->data.expression))
    {
        if (parent->type != NODE_LOG_OPERATOR && parent->type != NODE_OPERATOR
            && parent->type != NODE_REDIRECTION)
            return (1);
    }
    return (0);
}
// check_cmd_node(t_tree *node)
// {
        
// }