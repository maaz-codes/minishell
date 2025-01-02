/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:39:41 by rcreer            #+#    #+#             */
/*   Updated: 2025/01/02 15:43:21 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	tmp_looper(int *f, t_exp *tmp)
{
	*f = 0;
	while (tmp->exp[*f] != '=' && tmp->exp[*f])
		*f += 1;
}

void	plus_append(t_path **paths, char *tmp_char, char *sep)
{
	char	*joined_str;

	joined_str = ft_strjoin(tmp_char, sep);
	ap_exp(&(*paths)->exp_struct, joined_str);
	free(joined_str);
}
