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
                printf("%s\n",av[i++]);
            }
            free(input);
            free(av);
            i = 0;
        }
    }
    return 0;
}