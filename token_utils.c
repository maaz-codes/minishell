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
