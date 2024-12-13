/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:11:22 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/12 20:35:03 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	find_docs(t_tree *tree, t_ancient *ancient_one)
{
	if (tree->type == NODE_REDIRECTION)
		if (ft_strncmp(tree->data.redirection, "<<", 2) == 0)
		{
			tree->right->type = NODE_HEREDOC;
			tree->right->data.here_doc = ft_here_doc(tree->right->data.expression, ancient_one);
		}
	if (tree->left != NULL)
	{
		find_docs(tree->left, ancient_one);
		if (tree->right != NULL)
			find_docs(tree->right, ancient_one);
	}
}

static void sig_newline(int sig)
{
    if(sig == SIGINT)
	{
    	signal_caught = SIGINT;
		close(STDIN_FILENO);
	}
}
static void	read_write(char *limiter, int write_to)
{
	char	*new_line;
	char	*line;
	while (1)
	{
		line = readline("> ");
		if(!line)
			break ;
		if(signal_caught == SIGINT)
		{
			printf("enter here\n");
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
	
	signal(SIGINT,sig_newline);
	signal(SIGQUIT,SIG_IGN);
	if (pipe(doc_pipe) == -1)
	{
		(close(doc_pipe[1]),close(doc_pipe[0]));
		print_error(ERR_PIPE);
	}
	pid = fork();
	if(pid == 0)
	{
		read_write(limiter, doc_pipe[1]);
		(close(doc_pipe[1]),close(doc_pipe[0]));
		mini_fuk(ancient_one);
		free(limiter);
		exit(1);
	}
	close(doc_pipe[1]);
	waitpid(pid,&status,0);
	if(signal_caught == SIGINT)
		(close(doc_pipe[1]),close(doc_pipe[0]));
	free(limiter);
    return (doc_pipe[0]);
}