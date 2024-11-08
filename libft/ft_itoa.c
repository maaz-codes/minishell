/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:13:32 by maakhan           #+#    #+#             */
/*   Updated: 2024/06/28 19:30:16 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*memory_alloc(char *num, int i)
{
	char	*ptr;
	int		j;

	j = 0;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	i--;
	while (i >= 0)
		ptr[j++] = num[i--];
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	long	temp;
	char	num[11];
	int		i;

	temp = n;
	i = 0;
	if (n < 0)
		temp = temp * -1;
	if (n == 0)
		num[i++] = '0';
	while (temp != 0)
	{
		num[i++] = (temp % 10) + '0';
		temp = temp / 10;
	}
	if (n < 0)
		num[i++] = '-';
	ptr = memory_alloc(num, i);
	if (!ptr)
		return (NULL);
	return (ptr);
}
