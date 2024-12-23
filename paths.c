/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:24:11 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 18:21:14 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cwd(void)
{
	char	cwd[1024];
	char	*res;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("error");
	res = new_path(cwd, 0);
	return (res);
}

t_path	*int_cd(void)
{
	t_path	*node_new;
	char	*str1;
	char	*str2;

	str1 = get_cwd();
	str2 = get_cwd();
	node_new = (t_path *)malloc(sizeof(t_path));
	if (node_new == NULL)
		return (NULL);
	node_new->pwd = str1;
	node_new->pwd_old = str2;
	node_new->next = NULL;
	return (node_new);
}

t_path	*init_paths(char **env)
{
	t_path	*paths;

	paths = int_cd();
	if (!paths)
		print_exit(ERR_MALLOC);
	paths->env_struct = int_env(env);
	if (!paths->env_struct)
		paths->env_struct = NULL;
	paths->exp_struct = int_exp(env);
	if (!paths->exp_struct)
		paths->exp_struct = NULL;
	return (paths);
}
