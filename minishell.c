/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:50:55 by maakhan           #+#    #+#             */
/*   Updated: 2025/01/13 14:56:14 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static char	**convert_env_from_list(t_env *env_list)
{
	char	**env;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * (list_length_env(env_list) + 1));
	i = 0;
	while (env_list)
	{
		env[i] = ft_strdup(env_list->env);
		if (!env[i])
			print_exit(ERR_MALLOC);
		i++;
		env_list = env_list->next;
	}
	env[i] = NULL;
	return (env);
}

static int	execution(t_tree *tree, char **env, t_shl *shl)
{
	if (!find_docs(tree, shl))
	{
		free_array(env);
		return (0);
	}
	tree->level = 0;
	if (tree->type == NODE_OP)
		shl->inside_pipe = TRUE;
	gallows(tree, env, shl->inside_pipe, shl);
	free_array(env);
	return (1);
}

static t_tree	*parsing(char *input, t_shl *shl)
{
	input = env_expansion(input, shl->paths->env_struct, shl);
	shl->head = tokenization(input, shl);
	if (!shl->head)
		free_array(shl->env);
	return (shl->head);
}

static void	shell_reset(t_shl **shl)
{
	t_std_fds	std_fds;

	(*shl)->env = convert_env_from_list((*shl)->paths->env_struct);
	dup_fds(&std_fds);
	(*shl)->std_fds = std_fds;
	(*shl)->inside_pipe = FALSE;
	(*shl)->head = NULL;
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_tree	*tree;
	t_shl	*shl;
	t_path	*paths;

	if (ac != 1 || av[1] != NULL)
		return (write(2, "This shell doesn't take any args\n", 34), 1);
	paths = init_paths(env);
	shl = init_shell(paths);
	if (!isatty(0))
		rl_outstream = stdin;
	while (1)
	{
		shell_reset(&shl);
		input = signal_checkpoint(&shl->std_fds, shl);
		if (input)
		{
			add_history(input);
			tree = parsing(input, shl);
			if (tree)
				execution(tree, shl->env, shl);
			reset_std_fds(&shl->std_fds);
			nuke(shl, 0);
		}
	}
}
