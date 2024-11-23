#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

void find_docs(t_tree *tree)
{
	if (tree->type == NODE_REDIRECTION)
		if (ft_strncmp(tree->data.redirection, "<<", 2) == 0)
        	tree->right->data.here_doc = ft_here_doc(tree->right->data.expression);
	if (tree->left != NULL)
	{
		find_docs(tree->left);
		if (tree->right != NULL)
			find_docs(tree->right);
	}
}

int	main(int ac, char **av, char **env)
{
	char *input;
	t_tree *tree;

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
					find_docs(tree);
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
