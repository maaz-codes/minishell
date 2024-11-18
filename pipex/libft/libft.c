/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:26:53 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/18 16:46:59 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	pipex_ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	pipex_ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*pipex_ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (i <= pipex_ft_strlen(s))
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*pipex_ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (pipex_ft_strlen(s1) + 1));
	if (!ptr)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*pipex_ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	if (!s1)
		return (pipex_ft_strdup(s2));
	ptr = (char *)malloc(sizeof(char) * ((pipex_ft_strlen(s1) + pipex_ft_strlen(s2)) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ptr[i++] = s2[j++];
	}
	ptr[i] = '\0';
	return (ptr);
}
