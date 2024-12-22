/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:50:55 by maakhan           #+#    #+#             */
/*   Updated: 2024/12/22 17:23:21 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execution(t_tree *tree, char **env, t_ancient *ancient_one)
{
	if (!find_docs(tree, ancient_one))
		return (0);
	tree->level = 0;
	if (tree->type == NODE_OPERATOR)
		ancient_one->inside_pipe = TRUE;
	gallows(tree, env, ancient_one->inside_pipe, ancient_one);
	return (1);
}

static t_tree	*parsing(char *input, t_ancient *ancient_one)
{
	ancient_one->head = tokenization(input, ancient_one);
	expansions(&(ancient_one->head), ancient_one->paths->env_struct);
	return (ancient_one->head);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_tree		*tree;
	t_ancient	*ancient_one;
	t_path		*paths;

	if (ac != 1 || av[1] != NULL)
		return (write(2, "This shell doesn't take any args\n", 34), 1);
	paths = init_paths(env);
	g_signal_caught = 0;
	while (1)
	{
		ancient_one = init_ancient(paths);
		input = signal_checkpoint(&ancient_one->std_fds, ancient_one);
		if (input)
		{
			add_history(input);
			tree = parsing(input, ancient_one);
			if (tree)
				execution(tree, env, ancient_one);
			reset_std_fds(&ancient_one->std_fds);
			mini_fuk(ancient_one, 0);
		}
	}
	return (EXIT_SUCCESS);
}
