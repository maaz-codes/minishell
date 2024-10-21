#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// char **tokenization(char *input)
// {
//     char **res;

//     res = ft_split("")
// }
int main(int ac, char **av)
{   
    while(1)
    {
        char *input;
        // char **tokens;

        input = readline("minishell> ");
        if(input) 
        {   
            if(!ft_strncmp(input,"exit",5))
                exit(EXIT_SUCCESS);
            // tokens = tokenization(input);
            //helllo
        }
    }
    return 0;
}