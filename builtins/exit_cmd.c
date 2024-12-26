/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:39:06 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/25 11:29:09 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char **str, t_shl *shl)
{
	write(2, "exit\n", 6);
	write(2, "minishell: exit: ", 18);
	write(2, &str[1], ft_strlen(str[1]));
	write(2, ": numeric argument required\n", 29);
	nuke(shl, TNT);
	exit(255);
}

void	neg_num_exit(unsigned long long exit_num, t_shl *shl)
{
	long	negative_num;

	negative_num = -exit_num;
	negative_num = negative_num % 256;
	(nuke(shl, TNT), printf("exit\n"), exit(negative_num));
}

unsigned long long	symbol_check(char *str, int *check)
{
	unsigned long long	exit_num;

	if (str[0] == '-')
	{
		exit_num = ft_atol(str + 1);
		*check = 0;
	}
	else
		exit_num = ft_atol(str);
	return (exit_num);
}

void	num_valid_check(unsigned long long e, int c, char **str,
		t_shl *shl)
{
	if (e > LONG_MAX && c == 1)
		error_msg(str, shl);
	else if (e > (ULONG_MAX - LONG_MIN) + 1 && c == 0)
		error_msg(str, shl);
}

void	exit_cmd(char **str, t_shl *shl)
{
	unsigned long long	exit_num;
	int					check;

	check = 1;
	if (!ft_strncmp(str[0], "exit", 5) && str[1] != NULL && str[2] != NULL)
	{
		(write(2, "exit\n", 6), write(2, "exit: too many arguments\n", 26));
		shl->exit_status = 1;
		return ;
	}
	else if (!ft_strncmp(str[0], "exit", 5) && str[1] != NULL)
	{
		valid_num(str[1], str, shl);
		exit_num = symbol_check(str[1], &check);
		num_valid_check(exit_num, check, str, shl);
		if (!check)
			neg_num_exit(exit_num, shl);
		if (exit_num >= 256 && check == 1)
			exit_num = exit_num % 256;
		(nuke(shl, TNT), write(2, "exit\n", 6),
			exit(exit_num));
	}
	else if (!ft_strncmp(str[0], "exit", 5) && str[1] == NULL)
		(nuke(shl, TNT), write(2, "exit\n", 6), exit(0));
}
