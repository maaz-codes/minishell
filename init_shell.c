/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:46:36 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/23 11:24:57 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shl	*init_shell(t_path *paths)
{
	t_shl		*shl;
	t_std_fds	std_fds;

	shl = malloc(sizeof(t_shl));
	if (!shl)
	{
		ft_lstclear_env(&shl->paths->env_struct);
		ft_lstclear_exp(&shl->paths->exp_struct);
		ft_lstclear_path(&shl->paths);
		print_exit(ERR_MALLOC);
	}
	dup_fds(&std_fds);
	shl->std_fds = std_fds;
	shl->paths = paths;
	shl->exit_status = 0;
	shl->inside_pipe = FALSE;
	shl->head = NULL;
	return (shl);
}

void	dup_fds(t_std_fds *std_fds)
{
	std_fds->std_in = dup(STDIN_FILENO);
	std_fds->std_out = dup(STDOUT_FILENO);
	std_fds->std_err = dup(STDERR_FILENO);
}

void	reset_std_fds(t_std_fds *std_fds)
{
	dup2(std_fds->std_in, STDIN_FILENO);
	dup2(std_fds->std_out, STDOUT_FILENO);
	dup2(std_fds->std_err, STDERR_FILENO);
}
