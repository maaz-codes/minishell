/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:36:05 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/24 12:41:27 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*substring;
	int		i;

	if (!s || !len || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		substring = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		substring = malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		substring[i] = s[start];
		i++;
		start++;
	}
	substring[i] = '\0';
	return (substring);
}
