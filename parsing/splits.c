#include "../minishell.h"

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
		{
			i = inside_qoutes(str[i], str, i);
			continue;
		}
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
	char *cmd_name;
	char *cmd_flags;

	// norminette: merge these two together (super simple)
	if (str[i] == '<' || str[i] == '>')
	{
		if (str[i + 1] == '<' || str[i + 1] == '>')
		{
			*node = init_redir_node(ft_substr(str, i, 2));
			cmd_name = exp_after_redir_node(str, j, i + 2, 2);
			if (cmd_name)
				add_node(node, init_exp_node(cmd_name, 0, ft_strlen(str)), LEFT); // in init_nodes - stop mallocing, instead pass the substr or strdup in init_nodes();
			cmd_flags = extract_file_name(str, i + 2, ft_strlen(str));
			if (cmd_flags)
				add_node(node, init_file_node(cmd_flags, 0, ft_strlen(str)), RIGHT);
		}
		else
		{
			*node = init_redir_node(ft_substr(str, i, 1));
			cmd_name = exp_after_redir_node(str, j, i + 1, 1);
			if (cmd_name)
				add_node(node, init_exp_node(cmd_name, 0, ft_strlen(str)), LEFT); // in init_nodes - stop mallocing, instead pass the substr or strdup in init_nodes();
			cmd_flags = extract_file_name(str, i + 1, ft_strlen(str));
			if (cmd_flags)
				add_node(node, init_file_node(cmd_flags, 0, ft_strlen(str)), RIGHT);
		}
		if ((*node)->left != NULL)
			tokenizer((*node)->left->data.expression, &(*node)->left);
		// if ((*node)->right != NULL)
		// 	tokenizer((*node)->right->data.expression, &(*node)->right);
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
			add_node(node, init_exp_node(str, j, i), LEFT);
			add_node(node, init_exp_node(str, i + 2, ft_strlen(str)), LEFT);
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
		add_node(node, init_exp_node(str, j, i), LEFT);
		add_node(node, init_exp_node(str, i + 1, ft_strlen(str)), LEFT);
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
			add_node(node, init_exp_node(str, *i + 1, ft_strlen(str)), LEFT);
			if ((*node)->left != NULL)
				tokenizer((*node)->left->data.expression, &(*node)->left);
		}
		return (1);
	}
	return (0);
}

int split_cmd(char *str, int i, t_tree **node)
{
	char *args;
	// t_tree *node_tmp;

	args = NULL;
	if (str[i] == ' ' || str[i] == '\0')
	{
		// replacing the pointer, not over-writing it // free it later
		// node_tmp = *node;
		*node = init_cmd_node(str, i);
		// free(node_tmp);
		args = ft_substr(str, i, ft_strlen(str) - i);
		if (!args)
			print_exit(ERR_MALLOC);
		add_node(node, init_args_node(args, (*node)->data.command), LEFT);
		// add_node(node, init_args_node(str, i, ft_strlen(str), (*node)->data.command), LEFT);
		return (1);
	}
	return (0);
}

char **split_args(char *str, char *cmd)
{
    int i;
	int j;
	int k;
    char **args;

    i = 0;
	j = 0;
	k = 0;
    args = malloc(sizeof(char *) * (count_args(str) + 3));
	if (!args)
		print_exit(ERR_MALLOC);
	args[k++] = remove_qoutes(ft_strdup(cmd));
	if (!(*str))
	{
		args[k] = NULL;
		return (args);
	}
    while (i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			continue ;
		}
		else
		{
			if (str[i] == ' ' || str[i] == '\0')
			{
				args[k] = remove_qoutes(ft_substr(str, j, i - j));
				k++;
				if (skip_spaces(str, &i))
				{
					if (str[i] == '\0')
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
