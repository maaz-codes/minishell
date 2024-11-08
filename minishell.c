#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

void	print_error(int code)
{
	if (code == WRONG_FORMAT)
		printf("Error: Wrong format\n");
}

int	inside_qoutes(int *qoutes, char c, char *str, int *i)
{
	(*i) += 1;
	*qoutes = !(*qoutes);
	while (*qoutes && str[*i])
	{
		if (str[*i] == c)
			*qoutes = !(*qoutes);
		(*i) += 1;
	}
	if (*qoutes == 0)
		return (1);
	return (0);
}
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

t_tree *init_op_node(char op)
{
	t_tree *node;

	node = malloc(sizeof(t_tree));
	node->type = NODE_OPERATOR;
	node->t_data.operator = op;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree *init_exp_node(char *str, int start, int end)
{
	t_tree *node;

	node = malloc(sizeof(t_tree));
	node->type = NODE_EXPRESSION;
	node->t_data.expression = ft_substr(str, start, end - start);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void add_node(t_tree **tree, t_tree *node)
{
	if (*tree == NULL)
	{
		*tree = node;
		return ;
	}
	if ((*tree)->left == NULL)
		(*tree)->left = node;
	else if ((*tree)->right == NULL)
		(*tree)->right = node;
}

void print_data(t_tree *tree)
{
	if (tree->type == NODE_EXPRESSION)
		printf("data: %s type: %d\n", tree->t_data.expression, tree->type);
	else if (tree->type == NODE_OPERATOR)
		printf("data: %c type: %d\n", tree->t_data.operator, tree->type);
}

void print_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
	{
		printf("left:");
		print_tree(tree->left);
		if (tree->right != NULL)
		{
			printf("right:");
			print_tree(tree->right);
		}
		else
			print_data(tree);
	}
	print_data(tree);
}

t_tree *tokenizer(char *str, t_tree **node)
{
	int	i;
	int j;
	int	qoutes;

	qoutes = 0;
	i = 0;
	j = i;
	printf("exp: %s\n", str);
	while (i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
			inside_qoutes(&qoutes, symbol_checker(str[i]), str, &i);
		if (str[i] == '"' || str[i] == '\'')
			continue ;
		if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == ' ') // opertors
		{
			if (str[i] == ' ')
				printf("cmd: %c\n", str[i - 1]);
			// add_node(node, init_op_node(str[i]));
			*node = init_op_node(str[i]);
			add_node(node, init_exp_node(str, j, i));
			add_node(node, init_exp_node(str, i + 1, ft_strlen(str)));
			// printf("left:%s \n", (*node)->left->t_data.expression);
			// j = i + 1;
			// i++;
			break ;
		}
		i++;
	}
	// printf("left: %s \n", (*node)->left->t_data.expression);
	// printf("right: %s \n", (*node)->right->t_data.expression);
	// print_tree(*node);
	if ((*node)->left != NULL)
	{
		// printf("left\n");
		tokenizer((*node)->left->t_data.expression, &(*node)->left);
	}
	if ((*node)->right != NULL)
	{
		// printf("right\n");
		tokenizer((*node)->right->t_data.expression, &(*node)->right);
	}
	return (*node);
}

int qoutes_checker(char *str)
{
	int	i;
	int	qoutes;

	qoutes = 0;
	i = 0;
	while (i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
			inside_qoutes(&qoutes, symbol_checker(str[i]), str, &i);
		if (str[i] == '"' || str[i] == '\'')
			continue ;
		i++;
	}
	if (qoutes == 0)
		return (1);
	return (0);
}

char	**tokenization(char *str)
{
	t_tree *tree;

	// if (qoutes_checker(str))
	// 	print_error(WRONG_FORMAT);
	tree = NULL;
	tokenizer(str, &tree);
	if (tree == NULL)
		print_error(WRONG_FORMAT);
	print_tree(tree);
	return (NULL);
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
