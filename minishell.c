#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	while (1)
	{
		char *input;
		char **args;
		input = readline("minishell> ");
		if (input)
		{
			if (!ft_strncmp(input, "exit", 5) || !ft_strncmp(input, "\"exit\"", 7))
			{
				printf("Exiting now.....");
				exit(EXIT_SUCCESS);
			}
			args = tokenization(input);
			free(input); // no need, coz we're freeing it inside tokenizer;
		}
	}
	return (0);
}
// echo hi > cat | ls & test.c | echo hi > out