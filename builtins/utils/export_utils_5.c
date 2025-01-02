/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:25:59 by maakhan           #+#    #+#             */
/*   Updated: 2025/01/02 15:44:05 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	checker_which_mode(char *str, char *tmp_char, int *check)
{
	int	i;

	(void)tmp_char;
	i = 0;
	*check = 1;
	while (str[i] != '=' && str[i])
		i++;
	if (i == ft_strlen(str))
		*check = 0;
}

void	append_check_equals(t_path **paths, char *only_str, char *joined_str,
		int check)
{
	if (!check)
		ap_exp(&(*paths)->exp_struct, only_str);
	else
		ap_exp(&(*paths)->exp_struct, joined_str);
	(free(joined_str), free(only_str));
}

void	exp_loop(t_exp *tmp, char *only_str, char *joined_str, int check)
{
	if (!check)
	{
		free(joined_str);
		free(only_str);
		return ;
	}
	else
	{
		free(tmp->exp);
		tmp->exp = joined_str;
		free(only_str);
	}
}

void	check_sep_export(char **sep, int *i, int *exit_status)
{
	if (!sep)
	{
		*i += 1;
		*exit_status = 1;
	}
}
