#include <stdio.h>

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
int end_checker(char *s)
{   
    char symbol;
    int i = 0;
    symbol = '\0';
    if(s[i] == '\'' ||s[i] == '"')
    {
        symbol = symbol_checker(s[i]);
        while(s[i] == symbol && s[i + 1] == symbol)
            i += 2;
        if(s[i] == '\'' ||s[i] == '"')
            end_checker(s + i);
        else
            return(i);
    }
    return(0);
}
int main(int ac, char **av)
{
    (void)ac;
    int i = 0;
    while(av[0][i])
    {
        while(av[0][i] != ' ' && av[0][i])
        {
            if(av[0][i] == '\'' || av[0][i] == '"')
                i += end_checker(av[0]);
            i++;
            printf("%c",av[0][i]);
        }
    }
}