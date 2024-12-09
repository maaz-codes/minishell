/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:11:22 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/10 16:40:09 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_catch_doc(int sig)
{
    if(sig == SIGINT)
    {
        signal_caught = SIGINT;
        exit(130);
    }
}
void set_signals_heredoc(char *line, char *new_line)
{	
	signal(SIGINT,sigint_catch_doc);
	signal(SIGQUIT,SIG_IGN);
	if(signal_caught == SIGINT)
	{
		if(line)
			free(line);
		if(new_line)
			free(new_line);
	}
}

void	find_docs(t_tree *tree)
{
	if (tree->type == NODE_REDIRECTION)
		if (ft_strncmp(tree->data.redirection, "<<", 2) == 0)
			tree->right->data.here_doc = ft_here_doc(tree->right->data.expression);
	if (tree->left != NULL)
	{
		find_docs(tree->left);
		if (tree->right != NULL)
			find_docs(tree->right);
	}
}

static void	read_write(char *limiter, int write_to)
{
	char	*new_line;
	char	*line;

	// set_signals_heredoc(line, new_line);
	while (1)
	{
		line = readline("> ");
		if(!line)
			break ;
		if (line)
		{	
			if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
				break ;
			new_line = ft_strjoin(line, "\n");
			write(write_to, new_line, ft_strlen(new_line));
			free_str(&new_line);
			free_str(&line);
		}
		free_str(&line);
	}
	close(write_to);
}

int	ft_here_doc(char *limiter)
{
	// pid_t	pid;
	char	**cmd;
	int		doc_pipe[2];

	if (pipe(doc_pipe) == -1)
		print_error(ERR_PIPE);
	read_write(limiter, doc_pipe[1]);
	// waitpid(pid,NULL,0);
    return (doc_pipe[0]);
}
