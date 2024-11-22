/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:11:22 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/22 12:48:23 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line/get_next_line.h"

static void	read_write(char *limiter, int write_to)
{
	char	*new_limiter;
	char	*line;

	new_limiter = ft_strjoin(limiter, "\n");
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(line, new_limiter, ft_strlen(new_limiter)))
			break ;
		write(write_to, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(new_limiter);
	free(line);
	close(write_to);
}

int	ft_here_doc(char *limiter)
{
	pid_t	pid;
	char	**cmd;
	int		doc_pipe[2];

	if (pipe(doc_pipe) == -1)
		print_error(ERR_PIPE);
	write(1, "<here_doc/>\n", 12);
	read_write(limiter, doc_pipe[1]);
    return (doc_pipe[0]);
}
