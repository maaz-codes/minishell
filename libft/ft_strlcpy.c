/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:06:53 by rcreer            #+#    #+#             */
/*   Updated: 2024/10/15 15:48:53 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*src && (i + 1) < dstsize)
	{
		*dst++ = *src++;
		i++;
	}
	if (i < dstsize)
		*dst = '\0';
	while (*src++)
		i++;
	return (i);
}
