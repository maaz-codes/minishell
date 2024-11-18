/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:23 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/18 16:39:03 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	pid_t	pid_last;
	pid_t	pid_first;
	int		pipefd[2];
	int		status;

	if (argc == 5)
	{
		if (pipe(pipefd) == -1)
			(pipex_print_error());
		pid_first = first_process(argv, env, pipefd);
		pid_last = last_process(argc, argv, env, pipefd);
		waitpid(pid_first, &status, 0);
		waitpid(pid_last, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status));
		return (EXIT_SUCCESS);
	}
	return (1);
}
