/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:50:55 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/23 17:48:16 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execution(t_tree *tree, char **env, t_shl *shl)
{
	if (!find_docs(tree, shl))
		return (0);
	tree->level = 0;
	if (tree->type == NODE_OP)
		shl->inside_pipe = TRUE;
	gallows(tree, env, shl->inside_pipe, shl);
	return (1);
}

static t_tree	*parsing(char *input, t_shl *shl)
{
	shl->head = tokenization(input, shl);
	expansions(&(shl->head), shl->paths->env_struct,
		shl);
	return (shl->head);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_tree		*tree;
	t_shl		*shl;
	t_path		*paths;

	if (ac != 1 || av[1] != NULL)
		return (write(2, "This shell doesn't take any args\n", 34), 1);
	paths = init_paths(env);
	shl = init_shell(paths);
	while (1)
	{
		shl->inside_pipe = FALSE;
		shl->head = NULL;
		input = signal_checkpoint(&shl->std_fds, shl);
		if (input)
		{
			add_history(input);
			tree = parsing(input, shl);
			if (tree)
				execution(tree, env, shl);
			reset_std_fds(&shl->std_fds);
			nuke(shl, 0);
		}
	}
}
