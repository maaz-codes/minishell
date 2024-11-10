#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int special_chars(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ';' || c == '$')
		return (1);
	return (0);
}


// return (no of tokens or -1 in case of failure)
// t_tree *tokenizer(char *str)
// {
// 	int	i;
// 	int	qoutes;
// 	int	tokens;
// 	int	spl_flag;

// 	qoutes = 0;
// 	tokens = 0;
// 	spl_flag = 0;
// 	i = 0;
// 	while (i <= ft_strlen(str))
// 	{
// 		if (special_chars(str[i]))
// 		{
// 			spl_flag = 1;
// 			tokens++;
// 			i++;
// 		}
// 		if (str[i] == '"' || str[i] == '\'')
// 			inside_qoutes(&qoutes, symbol_checker(str[i]), str, &i);
// 		if (str[i] == '"' || str[i] == '\'')
// 			continue ;
// 		spl_flag = delimiters(spl_flag, str, &i, &tokens);
// 		printf("%c tokens = %d spl_flag = %d\n", str[i], tokens, spl_flag);
// 		i++;
// 	}
// 	if (qoutes == 0)
// 		return (NULL);
// 	return (NULL);
// }

// returns 1 if the delimiter was spl_char, 0 if not.
// int	delimiters(char *str, int *i)
// {
// 	if (str[*i] == '\0')
// 	{
// 		if (spl_flag == FALSE)
// 			*tokens += 1;
// 		return (spl_flag);
// 	}
// 	if (str[*i] == ' ')
// 		*tokens += 1;
// 	while (str[*i] == ' ') //skipping_spaces
// 	{
// 		*i += 1;
// 		if (str[*i] != ' ')
// 			return (spl_flag);
// 	}
// 	spl_flag = 0;
// 	if (special_chars(str[*i]))
// 	{
// 		spl_flag = 1;
//         *tokens += 1;
// 	}
// 	return (spl_flag);
// }

int operator_split(char *str, t_tree **node, int i, int j)
{
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
	{
		*node = init_op_node(str[i]);
		add_node(node, init_exp_node(str, j, i)); // j is always zero maybe remove it.
		add_node(node, init_exp_node(str, i + 1, ft_strlen(str)));
		if ((*node)->left != NULL)
			tokenizer((*node)->left->data.expression, &(*node)->left);
		if ((*node)->right != NULL)
			tokenizer((*node)->right->data.expression, &(*node)->right);
		return (1);
	}
	return (0);
}

int cmd_split(char *str, int *i, t_tree **node)
{
	int qoutes;

	qoutes = 0;
	// qoutes_logic
		// while (str[*i] == ' ' && str[*i + 1] == ' ')
		// {
		// 	*i += 1;
		// 	return (0);
		// }
		// if (str[*i] == '"' || str[*i] == '\'')
		// {
		// 	inside_qoutes(&qoutes, symbol_checker(str[*i]), str, i);
		// }
	// else
	// {
		if (str[*i] == ' ' || str[*i] == '\0')
		{
			// replacing the pointer, not over-writing it // free it later
			*node = init_cmd_node(str, *i);
			if (str[*i] != '\0')
				add_node(node, init_args_node(str, *i + 1, ft_strlen(str)));
			return (1);
		}
	// }
	return (0);
}

int operator_ahead(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

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
			free(input);
		}
	}
	return (0);
}
