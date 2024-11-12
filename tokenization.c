#include "minishell.h"

void strip_spaces(char **str)
{
	char *striped;
	char *original;

	if (*str == NULL)
		return ;
	striped = ft_strtrim(*str, " ");
	if (!striped)
		print_exit(ERR_MALLOC);
	original = *str;
	*str  = striped;
	free(original);
}

t_tree *tokenizer(char *str, t_tree **node)
{
	int	i;
	int j;
	int	qoutes;

	qoutes = 0;
	i = 0;
	j = i;
	// printf("exp: -%s-\n", str);
	strip_spaces(&str);
	while (i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
			inside_qoutes(&qoutes, symbol_checker(str[i]), str, &i);
		if (str[i] == '"' || str[i] == '\'')
			continue ;
		if (split_spl_operator(str, node, i, j))
			break ;
		else if (split_operator(str, node, i, j) && !spl_operator_ahead(str, i))
			break ;
		else if (split_cmd(str, &i, node) && !operator_ahead(str, i))
				break ;
		// else if (split_args(str))
			
		i++;
	}
	return (*node);
}

char	**tokenization(char *str)
{
	t_tree *tree;

	if (!qoutes_checker(str))
		print_error(ERR_FORMAT);
	else
	{
		tree = NULL;
		tokenizer(str, &tree);
		if (tree == NULL)
			print_error(ERR_FORMAT);
		tree->level = 0;
		print_tree(tree);
	}
	return (NULL);
}