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
	dup2(STDIN_FILENO, std_fds->std_in);
	dup2(STDOUT_FILENO, std_fds->std_out);
	dup2(STDERR_FILENO, std_fds->std_err);
}

void execution(t_tree *tree, char **env)
{
	pid_t pid;

	find_docs(tree);
	tree->level = 0;
	gallows(tree, env, tree->type != NODE_OPERATOR); 
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_tree		*tree;
	t_env		*env_vars;
	t_std_fds 	std_fds;

	while (1)
	{
		dup_fds(&std_fds);
		input = readline("minishell> ");
		if (input)
		{
			add_history(input);
			if (!ft_strncmp(input, "exit", 5) || !ft_strncmp(input, "\"exit\"",
					7))
			{
				printf("Exiting now.....\n");
				exit(EXIT_SUCCESS);
			}
			// printf("old_str = -%s-\n", input);
			// printf("expanded_str = -%s-\n", env_expansion(input, env_vars));
			if (*input)
			{
				tree = tokenization(input);
				if (tree)
					execution(tree, env);
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
