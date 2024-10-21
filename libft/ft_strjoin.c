/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:02:22 by rcreer            #+#    #+#             */
/*   Updated: 2024/10/02 18:48:13 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	int		catlen;
	char	*s3;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	catlen = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	s3 = (char *)malloc(sizeof(char) * catlen);
	if (!s3)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}
