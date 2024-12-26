/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:11:21 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/26 17:47:38 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_env_var(char *str, int start, int *index)
{
	int		end;
	char	*env_var;

	end = start;
	if (str[start] == '?')
		start++;
	else
	{
		if (str[start] >= '0' && str[start] <= '9')
			start++;
		else
			while ((str[start] >= 'a' && str[start] <= 'z')
				|| (str[start] >= 'A' && str[start] <= 'Z') || str[start] == '_'
				|| (str[start] >= '0' && str[start] <= '9'))
				start++;
	}
	env_var = ft_substr(str, end, start - end);
	if (!env_var)
		return (NULL);
	if (ft_strlen(env_var) == 0)
		return (free(env_var), NULL);
	(*index) = start - 1;
	return (env_var);
}

char	*assign_env_value(char *env_var, t_env *env)
{
	char	*env_value;
	char	*env_compare;
	int		index;

	env_value = NULL;
	index = 0;
	while (env)
	{
		env_compare = extract_env_var(env->env, 0, &index);
		if (!ft_strncmp(env->env, env_var, ft_strlen(env_compare)))
		{
			env_value = ft_substr(env->env, ft_strlen(env_var) + 1,
					ft_strlen(env->env));
			if (!env_value)
				print_exit(ERR_MALLOC);
			return (free(env_var), free(env_compare), env_value);
		}
		env = env->next;
		free(env_compare);
	}
	free(env_var);
	env_value = ft_strdup("");
	if (!env_value)
		print_exit(ERR_MALLOC);
	return (env_value);
}

char	*expanded_str(char *str, char *env_var, int start, int end)
{
	char	*expanded;
	int		total_len;
	int		i;
	int		j;

	total_len = ft_strlen(str) + ft_strlen(env_var) - (end - start + 1);
	expanded = malloc(sizeof(char) * (total_len + 1));
	if (!expanded)
		return (free(env_var), free(str), NULL);
	i = -1;
	while (++i < start)
		expanded[i] = str[i];
	j = 0;
	while (env_var[j])
		expanded[i++] = env_var[j++];
	while (end < ft_strlen(str))
		expanded[i++] = str[++end];
	return (free(str), free(env_var), expanded);
}

char	*assign_value(char *env_var, t_env *env, t_shl *shl)
{
	if (ft_strncmp(env_var, "?", 1) == 0)
	{
		free(env_var);
		env_var = ft_itoa(shl->exit_status);
	}
	else
		env_var = assign_env_value(env_var, env);
	return (env_var);
}

char	*env_expansion(char *str, t_env *env, t_shl *shl)
{
	int		i;
	int		j;
	char	*env_var;

	i = 0;
	while (i <= ft_strlen(str))
	{
		if (str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			if (i == -1)
				return (str);
			continue ;
		}
		if (str[i] == '$')
		{
			j = i;
			env_var = extract_env_var(str, i + 1, &i);
			env_var = assign_value(env_var, env, shl);
			str = expanded_str(str, env_var, j, i);
		}
		i++;
	}
	return (str);
}
