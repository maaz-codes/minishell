/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:24:46 by maakhan           #+#    #+#             */
/*   Updated: 2025/01/23 11:03:49 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*new_path(char *cwd, int id)
{
	int		len;
	char	*new_path;

	len = ft_strlen(cwd);
	if (id == 1)
	{
		len -= 1;
		while (cwd[len] != '/' && cwd[len])
			len--;
		if (cwd[len] == '/' && len == 0)
			len += 1;
	}
	new_path = ft_calloc(len + 1, sizeof(char *));
	if (!new_path)
		return (NULL);
	ft_strlcpy(new_path, cwd, len + 1);
	if (access(new_path, X_OK | F_OK) == -1)
	{
		error_msg_access();
		free(new_path);
		g_signal_caught = SIGINT;
		return (NULL);
	}
	return (get_new_cwd(new_path));
}

char	*get_home(t_path **paths)
{
	t_env	*tmp;
	char	**holder;
	char	*res;

	tmp = (*paths)->env_struct;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, "HOME=", 5))
		{
			holder = ft_split(tmp->env, '=');
			res = new_path(holder[1], 0);
			free_array(holder);
			if (chdir(res) == -1)
				(free(res), write(2, "error home\n", 12));
			return (res);
		}
		tmp = tmp->next;
	}
	write(2, "minishell: cd: HOME not set\n", 29);
	g_signal_caught = SIGINT;
	return (NULL);
}

int	valid_old_pwd(t_path **paths)
{
	t_env		*tmp;
	char		**old_pwd;
	struct stat	stat_check;

	tmp = (*paths)->env_struct;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, "OLDPWD=", 7))
		{
			old_pwd = separator(tmp->env, 0);
			if (stat(old_pwd[1], &stat_check) != 0)
			{
				write(2, "cd: ", 5);
				write(2, "No such file or directory\n", 27);
				g_signal_caught = SIGINT;
				free_array(old_pwd);
				return (0);
			}
			free_array(old_pwd);
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*switch_cd(t_path **paths)
{
	t_path	*temp;
	char	*res;

	if (!check_old_pwd(paths))
	{
		write(2, "OLDPWD is not set\n", 19);
		g_signal_caught = SIGINT;
		return (NULL);
	}
	if (!valid_old_pwd(paths))
		return (NULL);
	append_switch_struct(paths, &temp);
	(add_new_pwd(paths, temp), add_old_pwd(paths, temp));
	ft_lstadd_back_path(paths, temp);
	res = ft_strdup(temp->pwd);
	if (chdir(res) == -1)
	{
		(write(2, "error switch:\n", 15), free(res));
		g_signal_caught = SIGINT;
		return (NULL);
	}
	printf("new path: %s\n", res);
	return (res);
}

void	cd_cmd(char **str, t_path **paths, t_shl *shl)
{
	char	*res;
	int		check;
	char	cwd[1024];

	check = 0;
	res = NULL;
	getcwd(cwd, sizeof(cwd));
	if (!ft_strncmp(str[0], "cd", 3) && str[1] == NULL)
		res = get_home(paths);
	else if (!ft_strncmp(str[0], "cd", 3) && (!ft_strncmp(str[1], "~", 2)))
		res = get_home(paths);
	else if (str[1] != NULL && (!ft_strncmp(str[1], "..", 3)))
		res = new_path(cwd, 1);
	else if (str[1] != NULL && (!ft_strncmp(str[1], "-", 2)))
	{
		res = switch_cd(paths);
		check = 1;
	}
	else if (str[1] != NULL)
		res = new_path(str[1], 0);
	if (check == 0 && res)
		ft_append(paths, res, shl);
	if (res)
		free(res);
}
