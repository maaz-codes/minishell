#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

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

void execution(t_tree *tree, char **env, t_tree *ancient_one)
{
	pid_t pid;

	find_docs(tree);
	tree->level = 0;
	gallows(tree, env, tree->type == NODE_OPERATOR, ancient_one); 
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_tree		*tree;
	t_env		*env_vars;
	t_std_fds 	std_fds;
	t_tree 		*ancient_one;

	dup_fds(&std_fds);
	while (1)
	{
		input = readline("minishell> ");
		if (input)
		{
			add_history(input);
			if (!ft_strncmp(input, "exit", 5) || !ft_strncmp(input, "\"exit\"", 7))
			{
				printf("Exiting now.....\n");
				exit(EXIT_SUCCESS);
			}
			// printf("old_str = -%s-\n", input);
			// printf("expanded_str = -%s-\n", env_expansion(input, env_vars));
			if (*input)
			{
				tree = tokenization(input);
				ancient_one = tree;
				if (tree)
					execution(tree, env, ancient_one);
				printf("alive\n");
				lumberjack(tree);
				reset_std_fds(&std_fds);
			}
			// free(input); // no need, coz we're freeing it inside tokenizer;
		}
		else
		{
			printf("readline failure\n");
			exit(1);
		}
	}
	return (0);
}
