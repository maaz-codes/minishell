/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:01 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/18 16:48:02 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>

# define BUFFER_SIZE 5

// libft
size_t	pipex_ft_strlen(const char *str);
int		pipex_ft_strncmp(const char *s1, const char *s2, size_t n);
char	*pipex_ft_strchr(const char *s, int c);
char	*pipex_ft_strdup(const char *s1);
char	*pipex_ft_strjoin(char const *s1, char const *s2);
char	**pipex_ft_split(const char *s, char c);
char	*pipex_ft_strtrim(char const *s1, char const *set);

// paths
char	**set_cmd_arguments(char *cmd);
char	**extract_path_env(char **env);
char	*set_own_path(char *cmd);
char	*ft_cmd_exits(char **env, char *cmd);
int		count_cmds(char *argv[], int argc);

// processes
void	execute(char **cmd, char *env[], int read_from, int write_to);
pid_t	first_process(char **argv, char **env, int *pipefd);
pid_t	middle_process(char *argv_cmd, char **env, int read_from, int *pipefd);
pid_t	last_process(int argc, char **argv, char **env, int *pipefd);
void	pipeline(int argc, char **argv, char **env, int *pipefd);
void	close_stds(void);

// errors
void	pipex_print_error(void);
void	pipex_free_array(char **array);

// here_doc
int		ft_here_doc(char *limiter, char **argv, char **env, int *pipefd);

#endif