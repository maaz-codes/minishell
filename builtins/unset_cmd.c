/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:39:28 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/23 12:38:20 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_node_exp(t_path **paths, int pos)
{
	t_exp	*tmp_exp;
	t_exp	*prev_exp;
	int		i;

	i = 0;
	tmp_exp = (*paths)->exp_struct;
	while (tmp_exp)
	{
		if (i == pos)
			break ;
		i++;
		prev_exp = tmp_exp;
		tmp_exp = tmp_exp->next;
	}
	if (tmp_exp == NULL)
		return ;
	if (prev_exp != NULL)
		prev_exp->next = tmp_exp->next;
	else
		(*paths)->exp_struct = tmp_exp->next;
	free(tmp_exp->exp);
	free(tmp_exp);
}

void	remove_node_env(t_path **paths, int pos)
{
	t_env	*tmp_env;
	t_env	*prev_env;
	int		i;

	i = 0;
	tmp_env = (*paths)->env_struct;
	while (tmp_env)
	{
		if (i == pos)
			break ;
		i++;
		prev_env = tmp_env;
		tmp_env = tmp_env->next;
	}
	if (tmp_env == NULL)
		return ;
	if (prev_env != NULL)
		prev_env->next = tmp_env->next;
	else
		(*paths)->env_struct = tmp_env->next;
	free(tmp_env->env);
	free(tmp_env);
}

void	unset_exp_list(t_path **paths, char *str, int *i)
{
	t_exp	*tmp;
	int		pos;

	if (!valid_export(str, NULL, NULL, 0))
		i++;
	else
	{
		tmp = (*paths)->exp_struct;
		pos = 0;
		while (tmp)
		{
			if (!ft_strncmp(str, tmp->exp, ft_strlen(str)))
				break ;
			pos++;
			tmp = tmp->next;
		}
		remove_node_exp(paths, pos);
		*i += 1;
	}
}

void	unset_env_list(t_path **paths, char *str, int *i)
{
	t_env	*tmp;
	int		pos;

	if (!valid_export(str, NULL, NULL, 0))
		i++;
	else
	{
		tmp = (*paths)->env_struct;
		pos = 0;
		while (tmp)
		{
			if (!ft_strncmp(str, tmp->env, ft_strlen(str)))
				break ;
			pos++;
			tmp = tmp->next;
		}
		remove_node_env(paths, pos);
		*i += 1;
	}
}

void	unset_cmd(char **str, t_path **paths)
{
	t_exp	*tmp;
	int		i;

	i = 1;
	if (str[1] == NULL)
		return ;
	while (str[i])
		unset_exp_list(paths, str[i], &i);
	i = 1;
	while (str[i])
		unset_env_list(paths, str[i], &i);
}
