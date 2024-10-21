/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:57:53 by rcreer            #+#    #+#             */
/*   Updated: 2024/10/14 19:59:39 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	total_size;

	if (size && nmemb > (SIZE_MAX / size))
		return (NULL);
	total_size = nmemb * size;
	arr = malloc(total_size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, total_size);
	return (arr);
}
