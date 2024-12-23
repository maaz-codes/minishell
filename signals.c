/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:23:53 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/23 11:26:26 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*signal_checkpoint(t_std_fds *std_fds, t_shl *shl)
{
	char	*input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	input = readline("minishell> ");
	if (!input)
	{
		write(1, "exit\n", 6);
		reset_std_fds(std_fds);
		nuke(shl, FREE_PATH);
		exit(EXIT_SUCCESS);
	}
	if (g_signal_caught == SIGINT)
		shl->exit_status = 1;
	else if (g_signal_caught == 127)
		shl->exit_status = 127;
	else if (g_signal_caught == 0)
		shl->exit_status = 0;
	if (*input != '\0')
		g_signal_caught = 0;
	return (input);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_signal_caught = SIGINT;
	}
}
