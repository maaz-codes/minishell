#include "../minishell.h"

int inside_qoutes(char qoute, char (*str), int i)
{
    i++;
    while (str[i] != qoute && str[i])
    {
        i++;
    }
    if (str[i] == '\0')
        return (-1);
    return (i + 1);
}

int count_qoutes(char (*str))
{
    int  i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        // inside_qoutes()
        if (str[i] == '"' || str[i] == '\'')
            count++;
        i++;
    }
    return (0);
}

int qoutes_checker(char (*str))
{
	int	i;

	i = 0;
	while (i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
        {
            i = inside_qoutes(str[i], str, i);
            if (i == -1)
                return (0);
            continue;
        }
        if (!str[i])
            break ;
		i++;
	}
	return (1);
}

char *remove_qoutes(char (*str))
{
    int i;
    int j;
    int k;
    char *new_str;

    i = 0;
    j = 0;
    k = 0;
    new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
    if (!new_str)
        print_exit(ERR_MALLOC);
    while (i < ft_strlen(str))
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            j = i + 1;
			i = inside_qoutes(str[i], str, i);
            while (j < i - 1)
                new_str[k++] = str[j++];
            continue ;
        }
        new_str[k++] = str[i++];
    }
    new_str[k] = '\0';
    return (free(str), new_str);
}
