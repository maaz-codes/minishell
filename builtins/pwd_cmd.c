/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:39:22 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/26 16:06:58 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_cmd(char **str, t_shl *shl)
{
	char	cwd[1024];

	if (!ft_strncmp(str[0], "pwd", 3))
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s\n", cwd);
			g_signal_caught = 0;
			shl->exit_status = 0;
		}
		else
		{
			printf(".\n");
			return ;
		}
	}
}
