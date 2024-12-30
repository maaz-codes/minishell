/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:18:05 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/27 17:41:59 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_cwd(t_path **paths)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		write(2, "cd: error retrieving current directory: getcwd:", 48);
		write(2, "cannot access parent directories:", 34);
		write(2, " No such file or directory\n", 27);
		if (chdir((*paths)->pwd) == -1)
			return ;
	}
}

void 	check_exp_null(t_path **paths, t_exp *old_pwd)
{
	if((*paths)->exp_struct == NULL)
		(*paths)->exp_struct = old_pwd;
	else
		lstlast_exp((*paths)->exp_struct)->next = old_pwd;
}

void 	check_env_null(t_path **paths, t_env *old_pwd)
{
	if((*paths)->env_struct == NULL)
		(*paths)->env_struct = old_pwd;
	else
		lstlast_env((*paths)->env_struct)->next = old_pwd;
}
