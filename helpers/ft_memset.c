/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:08:41 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 17:08:42 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*hold;
	size_t	i;

	hold = b;
	i = 0;
	while (i < len)
	{
		*(char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (hold);
}
