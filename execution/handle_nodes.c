/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:17:00 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/23 11:46:40 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin(t_tree *tree, t_path *paths, t_shl *shl)
{
	if (!ft_strncmp(tree->data.cmd, "echo", 5))
		echo_cmd(tree->left->data.args, shl);
	else if (!ft_strncmp(tree->data.cmd, "pwd", 4))
		pwd_cmd(tree->left->data.args);
	else if (!ft_strncmp(tree->data.cmd, "cd", 3))
		cd_cmd(tree->left->data.args, &paths);
	else if (!ft_strncmp(tree->data.cmd, "export", 7))
		export_cmd(tree->left->data.args, &paths);
	else if (!ft_strncmp(tree->data.cmd, "unset", 6))
		unset_cmd(tree->left->data.args, &paths);
	else if (!ft_strncmp(tree->data.cmd, "env", 4))
		env_cmd(tree->left->data.args, &paths);
	else if (!ft_strncmp(tree->data.cmd, "exit", 5))
		exit_cmd(&paths, tree->left->data.args, shl);
}

void	handle_cmd(t_tree *tree, char **env, int pipe_flag, t_shl *shl)
{
	pid_t	pid;
	int		status;
	char	**args;

	args = array_dup(tree->left->data.args);
	if (!pipe_flag)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			nuke(shl, FREE_PATH);
			execute(args, env);
		}
		free_array(args);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) != 0)
			shl->exit_status = WEXITSTATUS(status);
	}
	else
	{
		nuke(shl, FREE_PATH);
		execute(args, env);
	}
}

void	handle_redir(t_tree *tree, char **env, int pipe_flag, t_shl *shl)
{
	int	fd;

	if (ft_strncmp(tree->data.redir, "<", 2) == 0)
		fd = handle_input_redir(tree->right->data.file, shl);
	else if (ft_strncmp(tree->data.redir, ">", 2) == 0)
		fd = handle_output_redir(tree->right->data.file, shl);
	else if (ft_strncmp(tree->data.redir, ">>", 2) == 0)
		fd = handle_append_redir(tree->right->data.file, shl);
	else if (ft_strncmp(tree->data.redir, "<<", 2) == 0)
		fd = handle_here_doc(tree->right->data.here_doc);
	if (fd != -1)
	{
		close(fd);
		gallows(tree->left, env, pipe_flag, shl);
	}
	else
	{
		shl->exit_status = 1;
		printf("exit_code: %d\n", shl->exit_status);
	}
	if (pipe_flag)
		exit(EXIT_SUCCESS);
}

void	handle_pipe(t_tree *tree, char **env, int pipe_flag, t_shl *shl)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
		(nuke(shl, FREE_PATH), print_exit(ERR_PIPE));
	pid_left = left_pipe(pipefd, tree, shl, env);
	pid_right = right_pipe(pipefd, tree, shl, env);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	if (WIFSIGNALED(status) != 0)
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit: 3", 8);
		else if (WTERMSIG(status) == SIGSEGV)
			write(2, "Segmentation fault: 11", 23);
		g_signal_caught = status + 128;
		shl->exit_status = status + 128;
	}
	if (tree->level != 1)
		(nuke(shl, FREE_PATH), exit(0));
}

int	handle_here_doc(int read_from)
{
	dup2(read_from, 0);
	close(read_from);
	return (read_from);
}

// printf("exit_code: %d\n", shl->exit_status);