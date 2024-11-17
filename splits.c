#include "minishell.h"

int count_args(char *str)
{
    int count;
    int qoutes;
    int i;

    count = 0;
    qoutes = 0;
    i = 0;
    while (i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
			inside_qoutes(&qoutes, symbol_checker(str[i]), str, &i);
		if (str[i] == '"' || str[i] == '\'')
			continue ;
		else
		{
			if (str[i] == ' ' || str[i] == '\0')
				count++;
			if (skip_spaces(str, &i))
			{
				i--;
				if (str[i + 1] == '\0')
					break ;
			}
        }
		i++;
	}
    return (count);
}

int split_redirection(char *str, t_tree **node, int i, int j)
{
	if (str[i] == '<' || str[i] == '>')
	{
		if (str[i + 1] == '<' || str[i + 1] == '>')
		{
			*node = init_redir_node(ft_substr(str, i, 2));
			add_node(node, init_exp_node(str, j, i));
			add_node(node, init_file_node(str, i + 2, ft_strlen(str)));
		}
		else
		{
			*node = init_redir_node(ft_substr(str, i, 1));
			add_node(node, init_exp_node(str, j, i));
			add_node(node, init_file_node(str, i + 1, ft_strlen(str)));
		}
		if ((*node)->left != NULL)
			tokenizer((*node)->left->data.expression, &(*node)->left);
		if ((*node)->right != NULL)
			tokenizer((*node)->right->data.expression, &(*node)->right);
		return (1);
	}
	return (0);
}
int split_log_operator(char *str, t_tree **node, int i, int j)
{
	if (str[i])
	{
		if ((str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i + 1] == '|'))
		{
			*node = init_log_op_node(str[i]);
			add_node(node, init_exp_node(str, j, i));
			add_node(node, init_exp_node(str, i + 2, ft_strlen(str)));
			if ((*node)->left != NULL)
				tokenizer((*node)->left->data.expression, &(*node)->left);
			if ((*node)->right != NULL)
				tokenizer((*node)->right->data.expression, &(*node)->right);
			return (1);
		}
	}
	return (0);
}

int split_operator(char *str, t_tree **node, int i, int j)
{
	if (str[i] == '|')
	{
		*node = init_op_node(str[i]);
		add_node(node, init_exp_node(str, j, i));
		add_node(node, init_exp_node(str, i + 1, ft_strlen(str)));
		if ((*node)->left != NULL)
			tokenizer((*node)->left->data.expression, &(*node)->left);
		if ((*node)->right != NULL)
			tokenizer((*node)->right->data.expression, &(*node)->right);
		return (1);
	}
	return (0);
}

int split_file(char *str, int *i, t_tree **node)
{
	if (str[*i] == ' ' || str[*i] == '\0')
	{
		// replacing the pointer, not over-writing it // free it later
		*node = init_file_node(str, 0, *i);
		if (str[*i] != '\0')
		{
			add_node(node, init_exp_node(str, *i + 1, ft_strlen(str)));
			if ((*node)->left != NULL)
				tokenizer((*node)->left->data.expression, &(*node)->left);
		}
		return (1);
	}
	return (0);
}

int split_cmd(char *str, int *i, t_tree **node)
{
	if (str[*i] == ' ' || str[*i] == '\0')
	{
		// replacing the pointer, not over-writing it // free it later
		*node = init_cmd_node(str, *i);
		if (str[*i] != '\0')
			add_node(node, init_args_node(str, *i + 1, ft_strlen(str), (*node)->data.command));
		return (1);
	}
	return (0);
}

char **split_args(char *str, char *cmd)
{
    int qoutes;
    int i;
	int j;
	int k;
    char **args;

    qoutes = 0;
    i = 0;
	j = 0;
	k = 0;
    args = malloc(sizeof(char *) * (count_args(str) + 3));
	if (!args)
		print_exit(ERR_MALLOC);
	args[k++] = remove_qoutes(ft_strdup(cmd));
    while (i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
			inside_qoutes(&qoutes, symbol_checker(str[i]), str, &i);
		if (str[i] == '"' || str[i] == '\'')
			continue ;
		else
		{
			if (str[i] == ' ' || str[i] == '\0')
			{
				args[k] = remove_qoutes(ft_substr(str, j, i - j));
				k++;
				if (skip_spaces(str, &i))
				{
					if (str[i + 1] == '\0')
						break ;
					i--;
				}
				j = i + 1;
			}
        }
		i++;
	}
	args[k] = NULL;
	return (args);
}
