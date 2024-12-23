/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:10:35 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/23 18:19:27 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_input_redir(char *file_name, t_shl *shl)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		print_error(ERR_FILE);
		return (fd);
	}
	if (dup2(fd, 0) == -1)
		(nuke(shl, TNT), print_exit(ERR_DUP));
	return (fd);
}

int	handle_output_redir(char *file_name, t_shl *shl)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(ERR_FILE);
		return (fd);
	}
	if (dup2(fd, 1) == -1)
		(nuke(shl, TNT), print_exit(ERR_DUP));
	return (fd);
}

int	handle_append_redir(char *file_name, t_shl *shl)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error(ERR_FILE);
		return (fd);
	}
	if (dup2(fd, 1) == -1)
		(nuke(shl, TNT), print_exit(ERR_DUP));
	return (fd);
}

pid_t	left_pipe(int *pipefd, t_tree *tree, t_shl *shl, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(nuke(shl, TNT), print_exit(ERR_FORK));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(pipefd[0]);
		if (dup2(pipefd[1], 1) == -1)
			(nuke(shl, TNT), print_exit(ERR_DUP));
		close(pipefd[1]);
		gallows(tree->left, env, 1, shl);
	}
	return (pid);
}

pid_t	right_pipe(int *pipefd, t_tree *tree, t_shl *shl,
		char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(nuke(shl, TNT), print_exit(ERR_FORK));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(pipefd[1]);
		(dup2(pipefd[0], 0), close(pipefd[0]));
		gallows(tree->right, env, 1, shl);
	}
	return (pid);
}
