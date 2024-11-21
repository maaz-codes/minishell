#include "minishell.h"

char	*set_own_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (cmd);
	return (NULL);
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
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	absoulute_paths = ft_split(path, ':');
	free(path);
	return (absoulute_paths);
}

char	*ft_cmd_exits(char **env, char *temp_cmd)
{
	char	**a_paths;
	char	*temp_str_join;
	char	*path;
	int		i;
	char	*cmd;

	path = NULL;
	cmd = ft_strtrim(temp_cmd, " ");
	a_paths = extract_path_env(env);
	if (!cmd || set_own_path(cmd) || !a_paths)
		return (free(a_paths), ft_strdup(cmd));
	i = -1;
	while (a_paths[++i])
	{
		temp_str_join = ft_strjoin(a_paths[i], "/");
		free(a_paths[i]);
		a_paths[i] = ft_strjoin(temp_str_join, cmd);
		free(temp_str_join);
		if (access(a_paths[i], F_OK) == 0 && access(a_paths[i], X_OK) == 0)
		{
			path = ft_strdup(a_paths[i]);
			break ;
		}
	}
	return (free_array(a_paths), free(cmd), path);
}