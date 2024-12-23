/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:46:36 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/23 10:32:26 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ancient	*init_ancient(t_path *paths)
{
	t_ancient	*ancient_one;
	t_std_fds	std_fds;

	ancient_one = malloc(sizeof(t_ancient));
	if (!ancient_one)
	{
		ft_lstclear_env(&ancient_one->paths->env_struct);
		ft_lstclear_exp(&ancient_one->paths->exp_struct);
		ft_lstclear_path(&ancient_one->paths);
		print_exit(ERR_MALLOC);
	}
	dup_fds(&std_fds);
	ancient_one->std_fds = std_fds;
	ancient_one->paths = paths;
	ancient_one->exit_status = 0;
	ancient_one->inside_pipe = FALSE;
	ancient_one->head = NULL;
	return (ancient_one);
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
