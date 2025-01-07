/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:39:41 by rcreer            #+#    #+#             */
/*   Updated: 2025/01/07 16:14:09 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	tmp_looper(int *f, t_exp *tmp, int *tmp_char_len, char *tmp_char)
{
	int	g;

	g = 0;
	*f = 0;
	while (tmp->exp[*f] != '=' && tmp->exp[*f])
		*f += 1;
	while (tmp_char[g] != '=' && tmp_char[g])
		g++;
	if (tmp_char[g] == '=')
		*tmp_char_len = ft_strlen(tmp_char) - 1;
	else
		*tmp_char_len = ft_strlen(tmp_char);
}

void	plus_append(t_path **paths, char *tmp_char, char *sep)
{
	char	*joined_str;

	joined_str = ft_strjoin(tmp_char, sep);
	ap_exp(&(*paths)->exp_struct, joined_str);
	free(joined_str);
}
