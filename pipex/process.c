/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:41:10 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/18 16:58:32 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char **cmd, char *env[], int read_from, int write_to)
{
	char	*path;

	path = ft_cmd_exits(env, cmd[0]);
	if (!path)
		(pipex_free_array(cmd), close(read_from), close(write_to), close_stds(),
			pipex_print_error());
	if (dup2(read_from, 0) < 0 || dup2(write_to, 1) < 0)
		(pipex_free_array(cmd), free(path), close(read_from), close(write_to),
			close_stds(), pipex_print_error());
	if (read_from != 0 || read_from != 1 || read_from != 2)
		close(read_from);
	if (write_to != 0 || write_to != 1 || write_to != 2)
		close(write_to);
	execve(path, cmd, env);
	(pipex_free_array(cmd), free(path), close_stds(), pipex_print_error());
}

pid_t	first_process(char **argv, char **env, int *pipefd)
{
	pid_t	pid;
	int		in_file;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		(close(pipefd[0]), close(pipefd[1]), close_stds(), pipex_print_error());
	if (pid == 0)
	{
		close(pipefd[0]);
		in_file = open(argv[1], O_RDONLY);
		if (in_file == -1)
			(close_stds(), close(pipefd[1]), pipex_print_error());
		cmd = set_cmd_arguments(argv[2]);
		if (!cmd)
			(close(in_file), close(pipefd[1]), write(2, "Error in cmd\n", 13),
				close_stds(), close(STDERR_FILENO), exit(127));
		execute(cmd, env, in_file, pipefd[1]);
	}
	return (pid);
}

pid_t	last_process(int argc, char **argv, char **env, int *pipefd)
{
	pid_t	pid;
	int		out_file;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		(close(pipefd[0]), close(pipefd[1]), close_stds(), pipex_print_error());
	if (pid == 0)
	{
		close(pipefd[1]);
		out_file = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (out_file == -1)
			(close(pipefd[0]), close_stds(), pipex_print_error());
		cmd = set_cmd_arguments(argv[argc - 2]);
		if (!cmd)
			(close(out_file), close(pipefd[0]), write(2, "Error in cmd\n", 13),
				close_stds(), close(STDERR_FILENO), exit(127));
		execute(cmd, env, pipefd[0], out_file);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (pid);
}

pid_t	middle_process(char *argv_cmd, char **env, int read_from, int *pipefd)
{
	pid_t	pid;
	char	**cmd;

	pid = fork();
	if (pid == -1)
		(close(read_from), close(pipefd[0]), close(pipefd[1]), close_stds(),
			pipex_print_error());
	if (pid == 0)
	{
		close(pipefd[0]);
		cmd = set_cmd_arguments(argv_cmd);
		if (!cmd)
			(close(read_from), close(pipefd[0]), close(pipefd[1]), close_stds(),
				write(2, "Error in cmd\n", 13), close(STDERR_FILENO),
				exit(127));
		execute(cmd, env, read_from, pipefd[1]);
	}
	return (pid);
}

void	pipeline(int argc, char **argv, char **env, int *pipefd)
{
	int	read_from;
	int	process_count;

	read_from = dup(pipefd[0]);
	process_count = count_cmds(argv, argc);
	while (process_count - 2)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		pipe(pipefd);
		middle_process(argv[argc - process_count], env, read_from, pipefd);
		close(read_from);
		read_from = dup(pipefd[0]);
		process_count--;
	}
	close(read_from);
}
