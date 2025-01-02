/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:11:14 by maakhan           #+#    #+#             */
/*   Updated: 2025/01/02 15:39:28 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_unset(char *str)
{
	int	i;
	int	check;
	int	len;

	len = 1;
	check = 1;
	i = 0;
	if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
		|| str[i] == '_')
		i++;
	else
		check = 0;
	if (!check)
		return (0);
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_' || (str[i] >= '0' && str[i] <= '9'))
			len++;
		i++;
	}
	if (len != ft_strlen(str))
		check = 0;
	return (check);
}

int	check_prev_env(int i, t_path **paths, t_env *prev_env, t_env *tmp_env)
{
	if (i == 0)
	{
		if ((*paths)->env_struct->next == NULL)
		{
			free(tmp_env->env);
			free(tmp_env);
			(*paths)->env_struct = NULL;
			return (0);
		}
		else
			(*paths)->env_struct = tmp_env->next;
	}
	else
		prev_env->next = tmp_env->next;
	return (1);
}

int	check_prev_exp(int i, t_path **paths, t_exp *prev_exp, t_exp *tmp_exp)
{
	if (i == 0)
	{
		if ((*paths)->exp_struct->next == NULL)
		{
			free(tmp_exp->exp);
			free(tmp_exp);
			(*paths)->exp_struct = NULL;
			return (0);
		}
		else
			(*paths)->exp_struct = tmp_exp->next;
	}
	else
		prev_exp->next = tmp_exp->next;
	return (1);
}
