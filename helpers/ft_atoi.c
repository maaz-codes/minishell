/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:07:30 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 17:08:24 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(char *s)
{
	int					conv;
	unsigned long long	res;

	conv = 1;
	res = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			conv *= -1;
		s++;
	}
	while (*s)
	{
		res = res * 10 + (*s - '0');
		if (res > LLONG_MAX && conv == -1)
			return (0);
		if (res > LLONG_MAX)
			return (-1);
		s++;
	}
	return (res * conv);
}
