/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:11:22 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/11 16:14:59 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_catch_doc(int sig)
{
    if(sig == SIGINT)
	{
        signal_caught = SIGINT;
		exit(0);
	}
	
}

void	find_docs(t_tree *tree, t_ancient *ancient_one)
{
	if (tree->type == NODE_REDIRECTION)
		if (ft_strncmp(tree->data.redirection, "<<", 2) == 0)
			tree->right->data.here_doc = ft_here_doc(tree->right->data.expression, ancient_one);
	if (tree->left != NULL)
	{
		find_docs(tree->left, ancient_one);
		if (tree->right != NULL)
			find_docs(tree->right, ancient_one);
	}
}

static void	read_write(char *limiter, int write_to)
{
	char	*new_line;
	char	*line;

	signal(SIGINT,SIG_DFL);
	signal(SIGQUIT,SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if(!line || signal_caught == SIGINT)
		{
			close(write_to);
			return ;
		}
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

int	ft_here_doc(char *limiter, t_ancient *ancient_one)
{	
	pid_t	pid;
	char	**cmd;
	int		doc_pipe[2];
	int		status;
	
	signal(SIGINT,SIG_IGN);
	if (pipe(doc_pipe) == -1)
	{
		(close(doc_pipe[1]),close(doc_pipe[0]));
		print_error(ERR_PIPE);
	}
	pid = fork();
	if(pid == 0)
	{
		close(doc_pipe[0]);
		read_write(limiter, doc_pipe[1]);
		exit(0);
	}
	close(doc_pipe[1]);
	waitpid(pid,&status,0);
	if(WIFSIGNALED(status) != 0)
	{
		ancient_one->exit_status = 1;
		signal_caught = 1;
	}
    return (doc_pipe[0]);
}
