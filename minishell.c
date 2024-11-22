#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	char *input;
	t_tree *tree;
	int std_in;
	int std_out;

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
			tree = tokenization(input);
			if (tree)
			{
				pid_t pid = fork();
				if (pid == 0)
				{
					std_in = dup(STDIN_FILENO);
					std_out = dup(STDOUT_FILENO);
					gallows(tree, env);
					printf("After gallows...\n");
					exit(0);
				}
				wait(NULL);
			}

			// free(input); // no need, coz we're freeing it inside tokenizer;
		}
	}
	return (0);
}
// echo hi > cat | ls & test.c | echo hi > out