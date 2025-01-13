/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:46:36 by maakhan           #+#    #+#             */
/*   Updated: 2025/01/13 16:23:09 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shl	*init_shell(t_path *paths)
{
	t_shl		*shl;

	shl = malloc(sizeof(t_shl));
	if (!shl)
	{
		// ft_lstclear_env(&shl->paths->env_struct);
		// ft_lstclear_exp(&shl->paths->exp_struct);
		// ft_lstclear_path(&shl->paths);
		print_exit(ERR_MALLOC);
	}
	shl->paths = paths;
	shl->e_stat = 0;
	shl->inside_pipe = FALSE;
	shl->head = NULL;
	shl->env = NULL;
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
