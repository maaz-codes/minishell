/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:39:22 by maakhan           #+#    #+#             */
/*   Updated: 2025/01/13 16:23:09 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char 	*find_curr_pwd(t_path **paths)
{
	t_exp	*tmp_exp;
	char 	*holder;
	tmp_exp = (*paths)->exp_struct;

	while (tmp_exp)
	{
		if (!ft_strncmp(tmp_exp->exp, "PWD=", 4))
		{	
			holder = ft_strchr(tmp_exp->exp, '=');
			return (holder + 1);
		}
		tmp_exp = tmp_exp->next;
	}
	return (NULL);
}
void	pwd_cmd(char **str, t_shl *shl, t_path **paths)
{
	char	cwd[1024];

	if (!ft_strncmp(str[0], "pwd", 3))
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s\n", cwd);
			g_signal_caught = 0;
			shl->e_stat = 0;
		}
		else
		{
			printf("%s\n",find_curr_pwd(paths));
			return ;
		}
	}
}
