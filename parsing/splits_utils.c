/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:17:24 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 17:17:40 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_cmd_from_redir(char *first_half, char *str, int start,
		int append)
{
	char	*cmd_flags;

	if (!first_half)
		(free(str), print_exit(ERR_MALLOC));
	cmd_flags = exp_after_redir_node(str, first_half, start + 1 + append);
	if (!cmd_flags)
		(free(first_half), free(str), print_exit(ERR_MALLOC));
	free(first_half);
	if (ft_strlen(cmd_flags) == 0)
		return (free(cmd_flags), NULL);
	return (cmd_flags);
}
