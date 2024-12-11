/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/11 13:48:05 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **array_dup(char **array)
{
    int i;
	int j;
    char **dup_array;

	i = 0;
	j = 0;
    if (!array)
        return NULL;
    while (array[i])
        i++;
    dup_array = (char **)malloc(sizeof(char *) * (i + 1));
    if (!dup_array)
        return NULL;
	while (j < i)
	{
		dup_array[j] = ft_strdup(array[j]);
		j++;
	}
    dup_array[i] = NULL;
    return (dup_array);
}

void	execute(char **cmd, char *env[], t_ancient *ancient_one)
{
	char	*path;
	struct stat directory;

	path = ft_cmd_exits(env, cmd[0]);
	if (!path)
		(reset_std_fds(ancient_one->std_fds), lumberjack(ancient_one->head), print_exit(ERR_CMD)); // free env as well...
	execve(path, cmd, env);
	if (stat(path, &directory) == 0)
	{
		write(2, "it's a directory\n", 18);
		free(path);
		reset_std_fds(ancient_one->std_fds), lumberjack(ancient_one->head);
		exit(126);
	}
	free(path);
	free_array(cmd);
	print_exit(ERR_CMD);
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

void left_pipe(int *pipefd, t_tree *tree, t_ancient *ancient_one, char **env)
{
	close(pipefd[0]);
	dup2(pipefd[1], 1), close(pipefd[1]);
	gallows(tree->left, env, 1, ancient_one);
}

void right_pipe(int *pipefd, t_tree *tree, t_ancient *ancient_one, char **env)
{
	close(pipefd[1]);
	dup2(pipefd[0], 0), close(pipefd[0]);
	gallows(tree->right, env, 1, ancient_one);
}

void	handle_pipe(t_tree *tree, char **env, int pipe_flag, t_ancient *ancient_one)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		print_exit(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		print_exit(ERR_FORK);
	if (pid == 0)
		left_pipe(pipefd, tree, ancient_one, env);
	pid = fork();
	if (pid == -1)
		print_exit(ERR_FORK);
	if (pid == 0)
		right_pipe(pipefd, tree, ancient_one, env);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	if (tree->level != 1) // not the main()
		exit(0);
}

void	handle_redir(t_tree *tree, char **env, int pipe_flag, t_ancient *ancient_one)
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
	{
		gallows(tree->left, env, pipe_flag, ancient_one);
	}
	if (pipe_flag)
		exit(1);
}

void	handle_cmd(t_tree *tree, char **env, int pipe_flag, t_ancient *ancient_one)
{
	pid_t	pid;
	char 	**args;

	args = array_dup(tree->left->data.argument);
	if (!pipe_flag)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			mini_fuk(ancient_one);
			// execute(tree->left->data.argument, env, ancient_one);
			execute(args, env, ancient_one);
		}
		free_array(args);
		wait(NULL);
	}
	else
	{
		mini_fuk(ancient_one);
		// execute(tree->left->data.argument, env, ancient_one);
		execute(args, env, ancient_one);
	}
	free_array(args);
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

void handle_builtin(t_tree *tree, t_path *paths, t_ancient *ancient_one)
{
    if (!ft_strncmp(tree->data.command, "echo", 5))
        echo_cmd(tree->left->data.argument);
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

int	gallows(t_tree *tree, char **env, int pipe_flag, t_ancient *ancient_one)
{
	if (tree == NULL)
		return 1;
	tree->level += 1;
	if (tree->type == NODE_OPERATOR)
		handle_pipe(tree, env, pipe_flag, ancient_one);
	else if (tree->type == NODE_REDIRECTION)
		handle_redir(tree, env, pipe_flag, ancient_one);
	else if (tree->type == NODE_COMMAND)
	{
		if (is_builtin(tree->data.command))
		{
			handle_builtin(tree, ancient_one->paths, ancient_one);
			if (pipe_flag)
			{
				mini_fuk(ancient_one);
				exit(EXIT_SUCCESS);
			}
		}
		else
			handle_cmd(tree, env, pipe_flag, ancient_one);
	}
	return (1);
}
