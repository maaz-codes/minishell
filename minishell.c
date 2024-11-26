#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

void	find_docs(t_tree *tree)
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

// echo '$USER =' $USER, Hello.

char	*extract_env_var(char *str, int start, int *index)
{
	int		end;
	char	*env_var;

	end = start;
	if (str[start] >= '0' && str[start] <= '9')
		start++;
	else
	{
		while ((str[start] >= 'a' && str[start] <= 'z') || (str[start] >= 'A'
				&& str[start] <= 'Z') || str[start] == '_' || (str[start] >= '0'
				&& str[start] <= '9'))
		{
			start++;
		}
	}
	env_var = ft_substr(str, end, start - end);
	if (!env_var)
		return (NULL);
	if ((*env_var) == '\0')
	{
		free(env_var);
		return (NULL);
	}
	(*index) = start - 1;
	return (env_var);
}

// char *assign_value(char **env_var)
// {
// 	// find the value and
// 	// re-assign the value to same env_var and 
// 	// free the previous one. 
// }

char	*env_expansion(char *str)
{
	int		i;
	char	*env_var;

	i = 0;
	while (i <= ft_strlen(str))
	{
		if (str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			continue ;
		}
		if (str[i] == '$')
		{
			env_var = extract_env_var(str, i + 1, &i);
			env_var = assign_value(&env_var);
		}
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_tree	*tree;

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
			// env_expansion(input);
			// free(input);
			// printf("expanded exp: =%s=\n", env_expansion(input));
			if (*input)
			{
				tree = tokenization(input);
				if (tree)
				{
					pid_t pid = fork();
					if (pid == 0)
					{
						find_docs(tree);
						gallows(tree, env);
						exit(0);
					}
					wait(NULL);
				}
			}
			// free(input); // no need, coz we're freeing it inside tokenizer;
		}
	}
	return (0);
}
