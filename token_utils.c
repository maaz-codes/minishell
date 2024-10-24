#include "minishell.h"

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
int malloc_safe(char **res, int position, size_t len)
{
    int i;

    i = 0;
    res[position] = malloc(len);
    if(!res[position])
    {
        while(i < position)
            free(res[i++]);
        free(res);
        return (0);
    }
    return(1);
}