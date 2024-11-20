/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/20 17:56:33 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex/pipex.h"

void handle_pipe(t_tree *tree, char **env)
{
    printf("duped STDin & STDout to reading & writing end of pipe\n");
    execution(tree->left, env);
    execution(tree->right, env);
}
void handle_redir(t_tree *tree, char **env)
{
    if (ft_strncmp(tree->data.redirection, ">", 2))
        printf("duped STDout to %s\n", tree->right->data.expression);
    else if (ft_strncmp(tree->data.redirection, "<", 2))
        printf("duped STDin to %s\n", tree->right->data.expression);
    execution(tree->left, env);
    
}

void handle_cmd(t_tree *tree, char **env)
{
    printf("executing {%s} with args: %s...\n", tree->data.command, tree->left->data.argument[1]);
}

void execution(t_tree *tree, char **env)
{
    printf("--EXECUTION--\n");
    if (tree->type == NODE_OPERATOR) // { | }
        handle_pipe(tree, env);
    else if (tree->type == NODE_REDIRECTION) // { > < >> << }
        handle_redir(tree, env);
    else if (tree->type == NODE_COMMAND)
        handle_cmd(tree, env);
}
