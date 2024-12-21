#include "minishell.h"

void dup_fds(t_std_fds *std_fds)
{
	std_fds->std_in = dup(STDIN_FILENO);
	std_fds->std_out = dup(STDOUT_FILENO);
	std_fds->std_err = dup(STDERR_FILENO);
}

void reset_std_fds(t_std_fds *std_fds)
{
	dup2(std_fds->std_in, STDIN_FILENO);
	dup2(std_fds->std_out, STDOUT_FILENO);
	dup2(std_fds->std_err, STDERR_FILENO);
}

int execution(t_tree *tree, char **env, t_ancient *ancient_one)
{
	if (!find_docs(tree,ancient_one))
		return (0);
	tree->level = 0;
	if (tree->type == NODE_OPERATOR)
		ancient_one->inside_pipe = TRUE;
	gallows(tree, env, ancient_one->inside_pipe, ancient_one);
	return (1);
}

t_ancient *init_ancient(char **env, t_path *paths)
{	
	(void) 		**env;
	t_ancient 	*ancient_one;
	t_std_fds 	std_fds;

	ancient_one = malloc(sizeof(t_ancient));
	if (!ancient_one)
	{
		ft_lstclear_env(&ancient_one->paths->env_struct);
		ft_lstclear_exp(&ancient_one->paths->exp_struct);
		ft_lstclear_path(&ancient_one->paths);
		print_exit(ERR_MALLOC);
	}
	dup_fds(&std_fds);
	ancient_one->std_fds = std_fds;
	ancient_one->paths = paths;
	ancient_one->exit_status = 0;
	ancient_one->inside_pipe = FALSE;
	ancient_one->head = NULL;
	return (ancient_one);
}

t_tree *parsing(char *input, t_ancient *ancient_one)
{
	// input = env_expansion(input, ancient_one->paths->env_struct);
	ancient_one->head = tokenization(input, ancient_one);
	// expansions(&ancient_one->head, ancient_one->paths->env_struct);
	// print_tree(ancient_one->head);
	return (ancient_one->head);
}

int	main(int ac, char **av, char **env)
{	
	(void)		**av;
	char		*input;
	t_tree		*tree;
	t_ancient 	*ancient_one;
	t_path		*paths;

	if (ac != 1)
		return (write(2, "This shell doesn't take any args\n", 34), 1);
	paths = init_paths(env);
	signal_caught = 0;
	while (1)
	{
		ancient_one = init_ancient(env, paths);
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
