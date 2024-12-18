/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/18 08:09:26 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char **cmd, char *env[])
{
	char		*path;
	struct stat	directory;

	if (ft_strlen(cmd[0]) == 0)
		(free_array(cmd), print_exit(ERR_CMD));
	path = ft_cmd_exits(env, cmd[0]);
	if (!path)
		(free_array(cmd), print_exit(ERR_CMD));
	execve(path, cmd, env);	
	if (stat(path, &directory) == 0)
	{
		write(2, "it's a directory\n", 18);
		free(path);
		free_array(cmd);
		exit(126);
	}
	else if (ft_strchr(path, '/'))
	{
		write(2, "No such file or directory\n", 27);
		free(path);
		free_array(cmd);
		exit(127);
	}
	(free(path), free_array(cmd), print_exit(ERR_CMD));
}

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3)
		|| !ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4)
		|| !ft_strncmp(str, "exit", 5))
	{
		return (1);
	}
	return (0);
}

int	gallows(t_tree *tree, char **env, int pipe_flag, t_ancient *ancient_one)
{
	if (tree == NULL)
		return (1);
	tree->level += 1;
	if (tree->type == NODE_OPERATOR)
		handle_pipe(tree, env, pipe_flag, ancient_one);
	else if (tree->type == NODE_REDIRECTION)
		handle_redir(tree, env, pipe_flag, ancient_one);
	else if (tree->type == NODE_COMMAND)
	{
		if (is_builtin(tree->data.command))
		{
			handle_builtin(tree, ancient_one->paths, ancient_one);
			if (pipe_flag)
			{
				mini_fuk(ancient_one, FREE_PATH);
				exit(EXIT_SUCCESS);
			}
		}
		else
			handle_cmd(tree, env, pipe_flag, ancient_one);
	}
	return (1);
}
