/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/18 16:56:03 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex/pipex.h"

void execution(t_tree *tree, char **env)
{
    char **cmd;
    
    pid_t pid = fork();
    // if (pid == -1)
        // print_error(ERR_FORK);
    if (pid == 0)
    {
        // cmd = set_cmd_arguments(tree->data.command);
        // if (!cmd)
            // do sm shit...
        execute(tree->left->data.argument, env, 0, 1);    
    }
}