/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/22 12:19:05 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **cmd, char *env[])
{
	char	*path;

	path = ft_cmd_exits(env, cmd[0]);
	if (!path)
		print_exit(ERR_MALLOC);
	execve(path, cmd, env);
	print_error(ERR_EXECVE);
    exit(1);
}

int handle_input_redir(char *file_name)
{
    int fd;
    
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        print_error(ERR_FILE);
        return (1);
    }
    dup2(fd, 0);
    return (fd);
}

int handle_output_redir(char *file_name)
{
    int fd;
    
    fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        print_exit(ERR_FILE);
        return (1);
    }
    dup2(fd, 1);
    return (fd);
}
int handle_append_redir(char *file_name)
{
    int fd;
    
    fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1)
    {
        print_error(ERR_FILE);
        return (1);
    }
    dup2(fd, 1);
    return (fd);
}
int handle_here_doc(int read_from)
{
    dup2(read_from, 0);
    close(read_from);
    return (1);
}

void handle_pipe(t_tree *tree, char **env)
{
    // duping STDin & STDout to reading & writing end of pipe
    pid_t pid;
    int pipefd[2];

    if (pipe(pipefd)== -1)
        print_exit(ERR_PIPE);
    pid = fork();
    if (pid == -1)
        print_exit(ERR_FORK);
    else if (pid == 0) // left-side
    {
        close(pipefd[0]);
        dup2(pipefd[1], 1), close(pipefd[1]);
        gallows(tree->left, env);
    }
    pid = fork();
    if (pid == -1)
        print_exit(ERR_FORK);
    else if (pid == 0) // right-side
    {
        close(pipefd[1]);
        dup2(pipefd[0], 0), close(pipefd[0]);
        gallows(tree->right, env);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
    exit (0);
}

void handle_redir(t_tree *tree, char **env)
{
    if (ft_strncmp(tree->data.redirection, "<", 2) == 0)
        handle_input_redir(tree->right->data.file);
    else if (ft_strncmp(tree->data.redirection, ">", 2) == 0)
        handle_output_redir(tree->right->data.file);
    else if (ft_strncmp(tree->data.redirection, ">>", 2) == 0)
        handle_append_redir(tree->right->data.file);
    else if (ft_strncmp(tree->data.redirection, "<<", 2) == 0)
        handle_here_doc(tree->right->data.here_doc);
    gallows(tree->left, env);
}

void handle_cmd(t_tree *tree, char **env)
{
    execute(tree->left->data.argument, env);   
}

void gallows(t_tree *tree, char **env)
{
    if (tree->type == NODE_OPERATOR) // { | }
        handle_pipe(tree, env);
    else if (tree->type == NODE_REDIRECTION) // { > < >> << }
        handle_redir(tree, env);
    else if (tree->type == NODE_COMMAND)
        handle_cmd(tree, env);
}
