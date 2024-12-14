/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:11:21 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/14 14:27:56 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_env_var(char *str, int start, int *index)
{
	int		end;
	char	*env_var;

	end = start;
	if (str[start] >= '0' && str[start] <= '9')
		start++;
	else
	{
		while ((str[start] >= 'a' && str[start] <= 'z') || (str[start] >= 'A'
				&& str[start] <= 'Z') || str[start] == '_' || (str[start] >= '0'
				&& str[start] <= '9'))
		{
			start++;
		}
	}
	env_var = ft_substr(str, end, start - end);
	if (!env_var)
		return (NULL);
	if (ft_strlen(env_var) == 0)
	{
		free(env_var);
		return (NULL);
	}
	(*index) = start - 1;
	return (env_var);
}

char	*assign_value(char *env_var, t_env *env)
{
	char	*env_value;

	env_value = NULL;
	printf("env=%s\n", env->env);
	while (env->env)
	{
		if (!ft_strncmp(env->env, env_var, ft_strlen(env_var)))
		{
			env_value = ft_substr(env->env, ft_strlen(env_var) + 1,
					ft_strlen(env->env));
			if (!env_value)
				print_exit(ERR_MALLOC);
			free(env_var);
			return (env_value);
		}
		env = env->next;
	}
	printf("came\n");
	free(env_var);
	env_value = ft_strdup("");
	if (!env_value)
		print_exit(ERR_MALLOC);
	return (env_value);
}

// modify the string and free everything...
// str = "echo This $my_var is amazing."
// env = "user" (value in $my_var)
// end => 'r'
// start => '$'
// malloc = strlen(str) - strlen("$my_var") + strlen(env_value);
char	*expanded_str(char *str, char *env_var, int start, int end)
{
	char	*expanded;
	int		total_len;
	int		i;

	total_len = ft_strlen(str) + ft_strlen(env_var) - (end - start + 1);
	expanded = malloc(sizeof(char) * (total_len + 1));
	if (!expanded)
	{
		free(env_var);
		free(str);
		return (NULL);
	}
	i = -1;
	while (++i < start) // "echo This "
		expanded[i] = str[i];
	while (*env_var) // "user"
	{
		expanded[i++] = *env_var;
		env_var++;
	}
	while (end < ft_strlen(str)) // " is amazing."
		expanded[i++] = str[++end];
	free(str);
	return (expanded);
}

char	*env_expansion(char *str, t_env *env)
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
			continue ;
		}
		if (str[i] == '$')
		{
			j = i;
			env_var = extract_env_var(str, i + 1, &i);
			printf("var_name: %s | str = %s\n", env_var, str);
			env_var = assign_value(env_var, env);
			if (str[i] != '$')
				str = expanded_str(str, env_var, j, i);
		}
		i++;
	}
	return (str);
}
