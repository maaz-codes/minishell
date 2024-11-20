#include "../minishell.h"

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
        if (str[i] == ';' || str[i] == '\\')
            return (0);
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

char *remove_qoutes(char *str)
{
    int i;
    int j;
    int k;
    int qoutes;
    char *new_str;

    i = 0;
    j = 0;
    k = 0;
    qoutes = 0;
    new_str = malloc(sizeof(char) * ft_strlen(str));
    if (!new_str)
        print_exit(ERR_MALLOC);
    while (i < ft_strlen(str))
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            j = i + 1;
			inside_qoutes(&qoutes, symbol_checker(str[i]), str, &i);
            while (j < i - 1)
                new_str[k++] = str[j++]; 
        }
		if (str[i] == '"' || str[i] == '\'')
			continue ;
        new_str[k++] = str[i++];
    }
    free(str);
    return (new_str);
}
