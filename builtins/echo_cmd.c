/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:11:19 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/23 12:50:54 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_dash_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] == 'n' && str[i])
			i++;
		if (ft_strlen(str) == i)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	n_check(int *checker, int *i, char **str)
{
	*checker = 1;
	while (str[*i])
	{
		if (valid_dash_n(str[*i]))
			*i += 1;
		else
			break ;
	}
}

void	echo_cmd(char **str, t_shl *shl)
{
	int	i;
	int	checker;
	int	f;

	checker = 0;
	i = 1;
	f = 0;
	if (!ft_strncmp(str[0], "echo", 5))
	{
		if (str[1] == NULL)
			checker = 0;
		else if (valid_dash_n(str[1]))
			n_check(&checker, &i, str);
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!checker)
		printf("\n");
}

		// else if (!ft_strncmp(str[1], "$?", 2))
		// 	return (printf("exit status: %d\n", shl->exit_status));