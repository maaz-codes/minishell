/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:06:53 by rcreer            #+#    #+#             */
/*   Updated: 2024/10/28 17:13:03 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*src && (i + 1) < dstsize)
	{	
		// if(*src == '"' || *src == '\'')
		// {
		// 	// printf("bruh");
		// 	src++;
		// 	i++;
		// }
		*dst++ = *src++;
		i++;
	}
	if (i < dstsize)
		*dst = '\0';
	while (*src++)
		i++;
	return (i);
}

size_t	ft_strlcpy_modif(char *dst, const char *src, size_t dstsize, char symbol)
{
	size_t	i;

	i = 0;
	while (*src && (i + 1) < dstsize)
	{	
		if(*src == symbol)
		{
			src++;
			i++;
		}
		*dst++ = *src++;
		i++;
	}
	if (i < dstsize)
		*dst = '\0';
	while (*src++)
		i++;
	return (i);
}

// int main()
// {
// 	char *s = "hello\"there\"man";
// 	char *res = malloc(1024);
// 	ft_strlcpy(res,s,16);
// 	while(*res)
// 	{
// 		printf("%c",*res++);
// 	}
	
// }
