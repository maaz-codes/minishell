#include "../minishell.h"

char symbol_checker(char s)
{   
    char symbol;

    symbol = '\0';
    if(s == '"')
        symbol = '"';
    if(s == '\'')
        symbol = '\'';
    return symbol;
}

int redirection_ahead(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			continue ;
		}
		if (str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

int spl_operator_ahead(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			continue ;
		}
		if ((str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i + 1] == '|'))
			return (1);
		i++;
	}
	return (0);
}

int operator_ahead(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			inside_qoutes(str[i], str, i);
			continue ;
		}
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int skip_spaces(char *str, int *i)
{
	int flag;

	flag = 0;
    while (str[*i] == ' ')
	{
		flag = 1;
        *i += 1;
	}
	return (flag);
}
