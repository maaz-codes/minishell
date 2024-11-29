/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/29 10:49:32 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **cmd, char *env[])
{
	char	*path;

	path = ft_cmd_exits(env, cmd[0]);
	if (!path)
		print_exit(ERR_CMD);
	execve(path, cmd, env);
	print_exit(ERR_CMD);
	exit(EXIT_FAILURE);
}

int	handle_input_redir(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		print_error(ERR_FILE);
		return (fd);
	}
	dup2(fd, 0);
	return (fd);
}

int	handle_output_redir(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_exit(ERR_FILE);
		return (fd);
	}
	dup2(fd, 1);
	return (fd);
}
int	handle_append_redir(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error(ERR_FILE);
		return (fd);
	}
	dup2(fd, 1);
	return (fd);
}
int	handle_here_doc(int read_from)
{
	dup2(read_from, 0);
	close(read_from);
	return (read_from);
}

void	handle_pipe(t_tree *tree, char **env, int pipe_flag)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		print_exit(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		print_exit(ERR_FORK);
	if (pid == 0) // left-side
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1), close(pipefd[1]);
		gallows(tree->left, env, pipe_flag);
	}
	pid = fork();
	if (pid == -1)
		print_exit(ERR_FORK);
	if (pid == 0) // right-side
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0), close(pipefd[0]);
		gallows(tree->right, env, pipe_flag);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	if (tree->level != 1) // not the main()
		exit(0);
}

void	handle_redir(t_tree *tree, char **env, int pipe_flag)
{
	int fd;
	
	if (ft_strncmp(tree->data.redirection, "<", 2) == 0)
		fd = handle_input_redir(tree->right->data.file);
	else if (ft_strncmp(tree->data.redirection, ">", 2) == 0)
		fd = handle_output_redir(tree->right->data.file);
	else if (ft_strncmp(tree->data.redirection, ">>", 2) == 0)
		fd = handle_append_redir(tree->right->data.file);
	else if (ft_strncmp(tree->data.redirection, "<<", 2) == 0)
		fd = handle_here_doc(tree->right->data.here_doc);
	if (fd != -1)
		gallows(tree->left, env, pipe_flag);
	if (pipe_flag)
		exit(1);
}

void	handle_cmd(t_tree *tree, char **env, int pipe_flag)
{
	pid_t	pid;

	if (!pipe_flag)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			execute(tree->left->data.argument, env);
		wait(NULL);
	}
	else
	{
		// printf("no fork for %s\n", tree->data.command);
		execute(tree->left->data.argument, env);
	}
    // exit(0);
	// exit_codes implementation...
}

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3)
		|| !ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4)
		|| !ft_strncmp(str, "exit", 5))
	{
		return (1);
	}
	return (0);
}

void handle_builtin(t_tree *tree, char **env)
{
    printf("Builtins in construction...\n");
    // if (!ft_strncmp(tree->data.command, "echo", 5))
    //     ft_echo();
    // else if (!ft_strncmp(tree->data.command, "cd", 3))
    //     ft_cd();
    // else if (!ft_strncmp(tree->data.command, "pwd", 4))
    //     ft_pwd();
    // else if (!ft_strncmp(tree->data.command, "export", 7))
    //     ft_export();
    // else if (!ft_strncmp(tree->data.command, "unset", 6))
    //     ft_unset();
    // else if (!ft_strncmp(tree->data.command, "env", 4))
    //     ft_env();
    // else if (!ft_strncmp(tree->data.command, "exit", 5))
    //     ft_exit();
}

int	gallows(t_tree *tree, char **env, int pipe_flag)
{
	tree->level += 1;
	if (tree->type == NODE_OPERATOR) // { | }
		handle_pipe(tree, env, pipe_flag);
	else if (tree->type == NODE_REDIRECTION) // { > < >> << }
		handle_redir(tree, env, pipe_flag);
	else if (tree->type == NODE_COMMAND)
	{
		if (is_builtin(tree->data.command))
			handle_builtin(tree, env);
		else
			handle_cmd(tree, env, pipe_flag);
	}
	return (1);
}
