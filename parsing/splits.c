#include "../minishell.h"

int count_args(char ((*str)))
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

char *extract_cmd_from_redir(char *first_half, char *str, int start, int append)
{
	char *cmd_flags;

	if (!first_half)
		print_exit(ERR_MALLOC);
	cmd_flags = exp_after_redir_node(str, first_half, start + 1 + append);
	if (!cmd_flags)
		(free(first_half), print_exit(ERR_MALLOC));
	free(first_half);
	return (cmd_flags);
}

int split_redirection(char **str, t_tree **node, int i, int j)
{
	t_tree *node_tmp;
	char *cmd;
	char *file_name;
	int append;

	append = 0;
	if ((*str)[i] == '<' || ((*str))[i] == '>')
	{
		node_tmp = *node;
		if (((*str))[i + 1] == '<' || (*str)[i + 1] == '>')
			append = 1;
		*node = init_redir_node(ft_substr((*str), i, 1 + append));
		cmd = extract_cmd_from_redir(ft_substr((*str), 0, i), (*str), i, append); // "cat -e"
		if (cmd)
			add_node(node, init_exp_node(&cmd), LEFT);
		file_name = extract_file_name((*str), i + 1 + append, ft_strlen(*str));
		if (file_name)
			add_node(node, init_file_node(file_name, 0, ft_strlen(*str)), RIGHT);
		free_str(str);
		free(node_tmp);
		if ((*node)->left != NULL)
			tokenizer(&cmd, &(*node)->left);
		return (1);
	}
	return (0);
}

int split_operator(char **str, t_tree **node, int i, int j) // remove j and put ancient_one
{
	t_tree *node_tmp;
	char *left_exp;
	char *right_exp;

	if ((*str)[i] == '|')
	{
		node_tmp = *node;
		*node = init_op_node((*str)[i]);
		left_exp = ft_substr(*str, j, i - j);
		if (!left_exp)
			(free_str(str), print_exit(ERR_MALLOC)); // call lumberJack();
		add_node(node, init_exp_node(&left_exp), LEFT);
		right_exp = ft_substr(*str, i + 1, ft_strlen(*str));
		if (!right_exp)
			(free_str(str), print_exit(ERR_MALLOC));
		add_node(node, init_exp_node(&right_exp), LEFT);
		// chop_branch(node_tmp);
		free_str(str);
		free(node_tmp);
		if ((*node)->left != NULL)
			tokenizer(&left_exp, &(*node)->left);
		if ((*node)->right != NULL)
			tokenizer(&right_exp, &(*node)->right);
		return (1);
	}
	return (0);
}

int split_cmd(char **str, int i, t_tree **node)
{
	char *args;
	char *cmd;
	t_tree *node_tmp;

	if ((*str)[i] == ' ' || (*str)[i] == '\0')
	{
		node_tmp = *node;
		cmd = ft_substr((*str), 0, i);
		*node = init_cmd_node(&cmd);
		args = ft_substr((*str), i, ft_strlen((*str)) - i); // this can be improved alot... just take the whole string as it is and then just split it with your split_args(), you dont even need cmd_name anymore.
		if (!args)
			print_exit(ERR_MALLOC);
		add_node(node, init_args_node(&args, (*node)->data.command), LEFT);
		free_str(str);
		free(node_tmp);
		// chop_branch(node_tmp);
		return (1);
	}
	return (0);
}

char **split_args(char (*str), char *cmd)
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
	if (!((*str)))
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
