/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:11:22 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 17:04:43 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_docs_ahead(t_tree *tree)
{
	if (tree->type == NODE_REDIRECTION && ft_strncmp(tree->data.redirection,
			"<<", 2) == 0)
		return (TRUE);
	if (tree->left != NULL)
		return (here_docs_ahead(tree->left));
	if (tree->right != NULL)
		return (here_docs_ahead(tree->right));
	return (FALSE);
}

int	find_docs(t_tree *tree, t_ancient *ancient_one)
{
	pid_t	pid;
	int		status;

	if (tree->type == NODE_REDIRECTION && ft_strncmp(tree->data.redirection,
			"<<", 2) == 0)
	{
		tree->right->data.here_doc = ft_here_doc(tree->right->data.expression,
				ancient_one, &pid);
		waitpid(pid, &status, 0);
		tree->right->type = NODE_HEREDOC;
		if (WEXITSTATUS(status) == 1)
		{
			ancient_one->exit_status = 1;
			g_signal_caught = SIGINT;
			return (close(tree->right->data.here_doc), FALSE);
		}
		if (tree->left != NULL)
			if (here_docs_ahead(tree->left) == TRUE)
				close(tree->right->data.here_doc);
	}
	if (tree->left != NULL)
	{
		return (find_docs(tree->left, ancient_one));
		if (tree->right != NULL)
			return (find_docs(tree->right, ancient_one));
	}
	return (1);
}

static void	handle_heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_caught = SIGINT;
		close(STDIN_FILENO);
	}
}

static void	read_write(char *limiter, int write_to, t_env *env)
{
	char	*new_line;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
				break ;
			new_line = ft_strjoin(line, "\n");
			write(write_to, env_expansion(new_line, env), ft_strlen(new_line));
			free_str(&new_line);
			free_str(&line);
		}
		free_str(&line);
	}
	close(write_to);
}

int	ft_here_doc(char *limiter, t_ancient *ancient_one, pid_t *pid)
{
	int	doc_pipe[2];
	int	status;

	if (pipe(doc_pipe) == -1)
		(close(doc_pipe[1]), close(doc_pipe[0]), print_error(ERR_PIPE));
	*pid = fork();
	if (*pid == -1)
		(mini_fuk(ancient_one, FREE_PATH), print_exit(ERR_FORK));
	if (*pid == 0)
	{
		signal(SIGINT, handle_heredoc_sig);
		signal(SIGQUIT, SIG_IGN);
		read_write(limiter, doc_pipe[1], ancient_one->paths->env_struct);
		close(doc_pipe[0]);
		(mini_fuk(ancient_one, FREE_PATH), exit(g_signal_caught == SIGINT));
	}
	close(doc_pipe[1]);
	free(limiter);
	return (doc_pipe[0]);
}
