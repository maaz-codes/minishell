/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:35:41 by maakhan           #+#    #+#             */
/*   Updated: 2024/07/03 15:09:59 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calculate_len(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

static size_t	check_needle(const char *haystack, const char *needle,
		int index)
{
	size_t	j;

	j = 0;
	while (needle[j] != '\0')
	{
		if (needle[j] == haystack[index])
		{
			j++;
			index++;
		}
		else
			break ;
	}
	return (j);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = calculate_len(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		if (needle[0] == haystack[i])
		{
			if (needle_len == check_needle(haystack, needle, i))
				if (len >= (i + needle_len))
					return ((char *)haystack + i);
		}
		i++;
	}
	return (0);
}
