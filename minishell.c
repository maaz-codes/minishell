#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_tree	*tree;
	t_env	*env_vars;

	while (1)
	{
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
			printf("old_str = -%s-\n", input);
			printf("expanded_str = -%s-\n", env_expansion(input, env_vars));
			// free(input);
			// printf("expanded exp: =%s=\n", env_expansion(input));
			// if (*input)
			// {
			// 	tree = tokenization(input);
			// 	if (tree)
			// 	{
			// 		pid_t pid = fork();
			// 		if (pid == 0)
			// 		{
			// 			find_docs(tree);
			// 			gallows(tree, env);
			// 			exit(0);
			// 		}
			// 		wait(NULL);
			// 	}
			// }
			// free(input); // no need, coz we're freeing it inside tokenizer;
		}
	}
	return (0);
}
