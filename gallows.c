/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/21 17:40:57 by maakhan          ###   ########.fr       */
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
    
    fd = open(file_name, O_CREAT | O_WRONLY, 0644);
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

void handle_pipe(t_tree *tree, char **env)
{
    printf("duped STDin & STDout to reading & writing end of pipe\n");
    gallows(tree->left, env);
    gallows(tree->right, env);
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
    gallows(tree->left, env);
}

void handle_cmd(t_tree *tree, char **env)
{
    // pid_t pid;
    // char *str[2];
    
    // str[0] = tree->data.command;
    // str[1] = NULL;
    // pid = fork();
    // if (pid == -1)
        // print_error(ERR_FORK);
    // if (pid == 0)
    // {
        execute(tree->left->data.argument, env);
    // }
    // wait(NULL);
}

void gallows(t_tree *tree, char **env)
{
    // printf("--EXECUTION--\n");
    if (tree->type == NODE_OPERATOR) // { | }
        handle_pipe(tree, env);
    else if (tree->type == NODE_REDIRECTION) // { > < >> << }
        handle_redir(tree, env);
    else if (tree->type == NODE_COMMAND)
        handle_cmd(tree, env);
}
