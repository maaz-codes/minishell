#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char **tokenization(char *input)
{
    char **res;
    int i = 0;


    res = ft_split(input,'"');
    return(res);
}

int checker(char *s)
{
    int i = 0;
    int in_double = -1;
    
    while(s[i] == ' ')
        i++;
    while(s[i])
    {   
        if(s[i] == '"')
            in_double *= -1;
        printf("%c",s[i]);
        i++;
    }
    if(in_double < 0)
        return 1;
    else
        return 0;
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
            if(!checker(input))
            {
                printf("\nNOT VALID\n");
                exit(EXIT_FAILURE);
            }
            printf("\nVALID\n");
            av = tokenization(input);
            // while(av[i])
            // {
            //     printf("string %d: %s\n",i,av[i]);
            //     i++;
            // }
            free(input);
            free_double(av);
            i = 0;
        }
    }
    return 0;
}