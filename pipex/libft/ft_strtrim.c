/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:05:05 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/18 16:47:37 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst || !src || !dstsize)
		return (pipex_ft_strlen(src));
	while ((i < dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (pipex_ft_strlen(src));
}

char	*pipex_ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = pipex_ft_strlen(s1);
		while (s1[i] && pipex_ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && pipex_ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		str = malloc(j - i + 1);
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, &s1[i], j - i + 1);
	}
	return (str);
}
