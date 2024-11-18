/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:52:06 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/18 16:46:59 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "pipex.h"

static void	read_write(char *limiter, int write_to)
{
	char	*new_limiter;
	char	*line;

	new_limiter = pipex_ft_strjoin(limiter, "\n");
	line = get_next_line(0);
	while (line)
	{
		if (!pipex_ft_strncmp(line, new_limiter, pipex_ft_strlen(new_limiter)))
			break ;
		write(write_to, line, pipex_ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(new_limiter);
	free(line);
	close(write_to);
}

int	ft_here_doc(char *limiter, char **argv, char **env, int *pipefd)
{
	pid_t	pid;
	char	**cmd;
	int		doc_pipe[2];

	if (pipe(doc_pipe) == -1)
		(close(pipefd[0]), close(pipefd[1]), pipex_print_error());
	write(1, "<here_doc/>\n", 12);
	read_write(limiter, doc_pipe[1]);
	pid = fork();
	if (pid == -1)
		(close(doc_pipe[0]), close(pipefd[0]), close(pipefd[1]), close_stds(),
			pipex_print_error());
	if (pid == 0)
	{
		close(pipefd[0]);
		cmd = set_cmd_arguments(argv[3]);
		if (!cmd)
			(close(doc_pipe[0]), close(pipefd[1]), close_stds(), write(2,
					"Error in cmd\n", 13), close(STDERR_FILENO), exit(127));
		execute(cmd, env, doc_pipe[0], pipefd[1]);
	}
	close(doc_pipe[0]);
	return (pid);
}
