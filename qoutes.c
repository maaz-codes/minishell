#include "minishell.h"

int inside_qoutes(int *qoutes, char c, char *str, int *i)
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

int count_qoutes(char *str)
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

// only accepts the cmd with or without qoutes
char *remove_qoutes(char *str)
{
    // "echo"""hello
    int i;
    int j; 
    char *cmd;
    char qoutes;
    int inside;

	qoutes = ' ';
    inside = 0;
    i = 0;
    j = 0;
    cmd = malloc(sizeof(char) * (ft_strlen(str) - count_qoutes(str)));
    while (str[i])
    {
        while ((str[i] == '"' || str[i] == '\'') || !inside)
        {
            qoutes = symbol_checker(str[i]);
            cmd[j++] = str[++i];
            if (str[i] == qoutes)
                inside = !inside;
        }
		if (str[i] == '"' || str[i] == '\'')
			continue ;
        i++;
    }
    return (NULL);
}
