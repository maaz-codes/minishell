/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:52:25 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/18 16:48:02 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_print_error(void)
{
	perror("Error");
	close(STDERR_FILENO);
	if (errno == ENOENT)
		exit(127);
	exit(1);
}

void	pipex_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	close_stds(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}
