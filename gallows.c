/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/27 19:20:36 by rcreer           ###   ########.fr       */
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
		return (1);
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
		return (1);
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
		return (1);
	}
	dup2(fd, 1);
	return (fd);
}
int	handle_here_doc(int read_from)
{
	dup2(read_from, 0);
	close(read_from);
	return (1);
}

void	handle_pipe(t_tree *tree, char **env, int fork_flag)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		print_exit(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		print_exit(ERR_FORK);
	else if (pid == 0) // left-side
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1), close(pipefd[1]);
		gallows(tree->left, env, fork_flag);
	}
	pid = fork();
	if (pid == -1)
		print_exit(ERR_FORK);
	else if (pid == 0) // right-side
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0), close(pipefd[0]);
		gallows(tree->right, env, fork_flag);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	// exit(0);
}

void	handle_redir(t_tree *tree, char **env, int fork_flag)
{
	if (ft_strncmp(tree->data.redirection, "<", 2) == 0)
		handle_input_redir(tree->right->data.file);
	else if (ft_strncmp(tree->data.redirection, ">", 2) == 0)
		handle_output_redir(tree->right->data.file);
	else if (ft_strncmp(tree->data.redirection, ">>", 2) == 0)
		handle_append_redir(tree->right->data.file);
	else if (ft_strncmp(tree->data.redirection, "<<", 2) == 0)
		handle_here_doc(tree->right->data.here_doc);
	gallows(tree->left, env, fork_flag);
}

void	handle_cmd(t_tree *tree, char **env, int fork_flag)
{
	pid_t	pid;

	if (fork_flag)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			execute(tree->left->data.argument, env);
		wait(NULL);
	}
	else
		execute(tree->left->data.argument, env);
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
    if(!ft_strncmp(tree->data.command, "echo", 5))
        echo_cmd(tree->left->data.argument);
    else if(!ft_strncmp(tree->data.command,"pwd",4))
        pwd_cmd(tree->left->data.argument);
    else if(!ft_strncmp(tree->data.command,"env",4))
	{
		// printf("inside env\n");
        env_cmd(tree->left->data.argument, tree);
	}
    // else if(!ft_strncmp(tree->left->data.argument[0],"cd",3))
    //     cd_cmd(env,&tree->paths);
    // else if(!ft_strncmp(env[0],"export",7))
    //     export_cmd(env,tree);
    // else if(!ft_strncmp(env[0],"unset",6))
    //     unset_cmd(env,tree);
    // else if (!ft_strncmp(env[0],"exit",5))
    //     exit_cmd(tree,env);
}

void	gallows(t_tree *tree, char **env, int fork_flag)
{
	if (tree->type == NODE_OPERATOR) // { | }
		handle_pipe(tree, env, fork_flag);
	else if (tree->type == NODE_REDIRECTION) // { > < >> << }
		handle_redir(tree, env, fork_flag);
	else if (tree->type == NODE_COMMAND)
	{
		if (is_builtin(tree->data.command))
			handle_builtin(tree, env);
		else
			handle_cmd(tree, env, fork_flag);
	}
}
