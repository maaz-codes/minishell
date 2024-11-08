/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:22:24 by maakhan           #+#    #+#             */
/*   Updated: 2024/06/28 19:28:05 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	temp;
	char	num[10];
	int		i;

	temp = n;
	if (temp < 0)
	{
		write(fd, "-", 1);
		temp = temp * -1;
	}
	if (temp == 0)
		write(fd, "0", 1);
	i = 0;
	while (temp != 0)
	{
		num[i] = (temp % 10) + '0';
		temp = temp / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		write(fd, &num[i], 1);
		i--;
	}
}
