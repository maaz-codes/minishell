#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char **tokenization(char *input)
{
    char **res;

    res = ft_split(input,' ');
    return(res);
}

void free_double(char **s)
{
    int i;

    i = 0;
    while(s[i])
        free(s[i++]);
    free(s);
}
int main(int ac, char **av)
{   
    while(1)
    {
        char *input;
        int i = 0;
        input = readline("minishell> ");
        if(input) 
        {   
            if(!ft_strncmp(input,"exit",5))
                exit(EXIT_SUCCESS);
            av = tokenization(input);
            while(av[i])
            {
                printf("string %d: %s\n",i,av[i]);
                i++;
            }
            free(input);
            free_double(av);
            i = 0;
        }
    }
    return 0;
}