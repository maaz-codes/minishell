/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:25:36 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 17:32:55 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*holder_env(char *str, int len, int check)
{
	char	*holder;
	char	*check_str;

	if (!str)
		return (NULL);
	if (!check)
	{
		holder = ft_calloc(len + 1, sizeof(char *));
		if (!holder)
			return (NULL);
		ft_strlcpy(holder, str, ft_strlen(str));
	}
	else
	{
		check_str = ft_strchr(str, '=');
		check_str++;
		holder = ft_strdup(check_str);
	}
	return (holder);
}

int	error_exp(char *str, char **res, char **sep)
{
	printf("export: \'%s\': not a valid identifier\n", str);
	if (res)
		free_array(res);
	if (sep)
		free_array(sep);
	return (0);
}

int	valid_export(char *str, char **res, char **sep, int check_for_plus)
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
		check = error_exp(str, res, sep);
	if (!check)
		return (0);
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_')
			len++;
		else if ((str[i] >= '0' && str[i] <= '9'))
			len++;
		i++;
	}
	if (len != ft_strlen(str) && !check_for_plus)
		check = error_exp(str, res, sep);
	return (check);
}

char	**append_exp(char *sep, char *holder)
{
	char	**res;
	char	*sep_str;
	char	*holder_str;

	sep_str = ft_strdup(sep);
	holder_str = ft_strdup(holder);
	res = (char **)malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	res[0] = sep_str;
	res[1] = holder_str;
	res[2] = NULL;
	return (res);
}

char	**separator(char *str, int check_for_plus)
{
	int		len;
	char	**sep;
	char	*holder;
	char	**res;
	int		check;

	sep = ft_split(str, '=');
	len = 0;
	check = 1;
	while (str[len] != '=' && str[len])
		len++;
	if (!len)
	{
		error_exp(str, NULL, sep);
		return (NULL);
	}
	if (ft_strlen(str) == len)
		check = 0;
	holder = holder_env(str, len, check);
	res = append_exp(sep[0], holder);
	free(holder);
	if (!valid_export(sep[0], res, sep, check_for_plus))
		return (NULL);
	free_array(sep);
	return (res);
}
