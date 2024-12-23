/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:25:28 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/23 12:52:06 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	valid_num(char *s, char **str, t_shl *shl)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			i++;
			len++;
		}
		else
			error_msg(str, shl);
	}
	if (len >= 20)
		error_msg(str, shl);
}
