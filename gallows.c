/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/21 18:37:13 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "pipex/pipex.h"

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
    return (0);
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
    return (0);
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
    return (0);
}
int handle_here_doc(char *delimiter)
{
    printf("HERE_DOC-ing\n");
    return (0);
}

void handle_pipe(t_tree *tree, char **env, int read_from, int write_to)
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
        gallows(tree->left, env, pipefd[0], pipefd[1]);
    pid = fork();
    if (pid == -1)
        print_exit(ERR_FORK);
    else if (pid == 0) // right-side
        gallows(tree->right, env, read_from, write_to);
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
        handle_here_doc(tree->right->data.file);
    gallows(tree->left, env, );
}

void handle_cmd(t_tree *tree, char **env)
{
    execute(tree->left->data.argument, env);   
}

void gallows(t_tree *tree, char **env, int read_from, int write_to)
{
    // printf("--EXECUTION--\n");
    dup2(read_from, 0);
    dup2(write_to, 1);
    if (tree->type == NODE_OPERATOR) // { | }
        handle_pipe(tree, env, read_from, write_to);
    else if (tree->type == NODE_REDIRECTION) // { > < >> << }
        handle_redir(tree, env);
    else if (tree->type == NODE_COMMAND)
        handle_cmd(tree, env);
}
