/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:43:57 by maakhan           #+#    #+#             */
/*   Updated: 2024/07/10 12:51:36 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		number = (number * 10) + (str[i] - '0');
		if (number > LLONG_MAX && sign == -1)
			return (0);
		if (number > LLONG_MAX)
			return (-1);
		i++;
	}
	return (number * sign);
}
int main()
{
	char *nbr = "2147483647199999999";
	printf("%d \n", ft_atoi(nbr));
	printf("%d \n", atoi(nbr));
}