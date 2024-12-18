/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:17:00 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/18 08:17:01 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin(t_tree *tree, t_path *paths, t_ancient *ancient_one)
{
	if (!ft_strncmp(tree->data.command, "echo", 5))
		echo_cmd(tree->left->data.argument, ancient_one);
	else if (!ft_strncmp(tree->data.command, "pwd", 4))
		pwd_cmd(tree->left->data.argument);
	else if (!ft_strncmp(tree->data.command, "cd", 3))
		cd_cmd(tree->left->data.argument, &paths);
	else if (!ft_strncmp(tree->data.command, "export", 7))
		export_cmd(tree->left->data.argument, &paths);
	else if (!ft_strncmp(tree->data.command, "unset", 6))
		unset_cmd(tree->left->data.argument, &paths);
	else if (!ft_strncmp(tree->data.command, "env", 4))
		env_cmd(tree->left->data.argument, &paths);
	else if (!ft_strncmp(tree->data.command, "exit", 5))
		exit_cmd(&paths, tree->left->data.argument, ancient_one);
}

void	handle_cmd(t_tree *tree, char **env, int pipe_flag,
		t_ancient *ancient_one)
{
	pid_t	pid;
	int		status;
	char	**args;

	args = array_dup(tree->left->data.argument);
	if (!pipe_flag)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			mini_fuk(ancient_one, FREE_PATH);
			execute(args, env);
		}
		free_array(args);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) != 0)
			ancient_one->exit_status = WEXITSTATUS(status);
	}
	else
	{
		mini_fuk(ancient_one, FREE_PATH);
		execute(args, env);
	}
}

void	handle_redir(t_tree *tree, char **env, int pipe_flag,
		t_ancient *ancient_one)
{
	int	fd;

	if (ft_strncmp(tree->data.redirection, "<", 2) == 0)
		fd = handle_input_redir(tree->right->data.file);
	else if (ft_strncmp(tree->data.redirection, ">", 2) == 0)
		fd = handle_output_redir(tree->right->data.file);
	else if (ft_strncmp(tree->data.redirection, ">>", 2) == 0)
		fd = handle_append_redir(tree->right->data.file);
	else if (ft_strncmp(tree->data.redirection, "<<", 2) == 0)
		fd = handle_here_doc(tree->right->data.here_doc);
	if (fd != -1)
		gallows(tree->left, env, pipe_flag, ancient_one);
	if (pipe_flag)
		exit(1);
}

void	handle_pipe(t_tree *tree, char **env, int pipe_flag,
		t_ancient *ancient_one)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
		(mini_fuk(ancient_one, FREE_PATH), print_exit(ERR_PIPE));
	pid_left = left_pipe(pipefd, tree, ancient_one, env);
	pid_right = right_pipe(pipefd, tree, ancient_one, env);
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
		signal_caught = status + 128;
		ancient_one->exit_status = status + 128;
	}
	if (tree->level != 1) // not the main()
		(mini_fuk(ancient_one, FREE_PATH), exit(0));
}

int	handle_here_doc(int read_from)
{
	dup2(read_from, 0);
	close(read_from);
	return (read_from);
}