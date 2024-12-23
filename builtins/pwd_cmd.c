/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:39:22 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/23 12:38:16 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_cmd(char **str, t_shl *shl)
{
	char	cwd[1024];

	if (str[1] != NULL)
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{	
		printf("%s\n", cwd);
		g_signal_caught = 0;
		shl->exit_status = 0;
	}
	else
	{
		printf("error");
		nuke(shl, TNT);
		exit(EXIT_FAILURE);
	}
}
