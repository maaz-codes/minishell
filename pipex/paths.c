/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:50:20 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/18 16:48:02 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_cmds(char *argv[], int argc)
{
	int	count;

	if (!pipex_ft_strncmp(argv[1], "here_doc", 9))
		count = argc - 4;
	else
		count = argc - 3;
	return (count);
}

// char *argv[] = {"/usr/bin/awk", "{count++} END {print count}", NULL};
char	**set_cmd_arguments(char *cmd)
{
	char	**cmd_args;

	if (strstr(cmd, "awk"))
		cmd_args = pipex_ft_split(cmd, '\'');
	else
		cmd_args = pipex_ft_split(cmd, ' ');
	if (!cmd_args)
		return (NULL);
	else if (!cmd_args[0])
	{
		pipex_free_array(cmd_args);
		return (NULL);
	}
	return (cmd_args);
}

char	**extract_path_env(char **env)
{
	int		i;
	char	*path;
	char	**absoulute_paths;

	i = 0;
	path = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (pipex_ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = pipex_ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	absoulute_paths = pipex_ft_split(path, ':');
	free(path);
	return (absoulute_paths);
}

char	*set_own_path(char *cmd)
{
	if (pipex_ft_strchr(cmd, '/'))
		return (cmd);
	return (NULL);
}

char	*ft_cmd_exits(char **env, char *temp_cmd)
{
	char	**a_paths;
	char	*temp_str_join;
	char	*path;
	int		i;
	char	*cmd;

	path = NULL;
	cmd = pipex_ft_strtrim(temp_cmd, " ");
	a_paths = extract_path_env(env);
	if (!cmd || set_own_path(cmd) || !a_paths)
		return (free(a_paths), pipex_ft_strdup(cmd));
	i = -1;
	while (a_paths[++i])
	{
		temp_str_join = pipex_ft_strjoin(a_paths[i], "/");
		free(a_paths[i]);
		a_paths[i] = pipex_ft_strjoin(temp_str_join, cmd);
		free(temp_str_join);
		if (access(a_paths[i], F_OK) == 0 && access(a_paths[i], X_OK) == 0)
		{
			path = pipex_ft_strdup(a_paths[i]);
			break ;
		}
	}
	return (pipex_free_array(a_paths), free(cmd), path);
}
