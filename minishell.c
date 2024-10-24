#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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
        char **res;
        int i = 0;
        input = readline("minishell> ");
        if(input) 
        {   
            if(!ft_strncmp(input,"exit",5))
                exit(EXIT_SUCCESS);
            res = tokenization_char(input);
            while(res[i])
            {
                printf("string %d: %s\n",i,res[i]);
                i++;
            }
            free(input);
            free_double(res);
            i = 0;
        }
    }
    return 0;
}