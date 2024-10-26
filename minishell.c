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

int space_checker(char *s)
{   
    int inside = 0;
    char symbol = '\0';
    int spaces = 0;
    while(*s)
    {   
        inside = 0;
        while(*s != ' ' && !(*s == '"' || *s == '\'') && *s)
            s++;
        if(*s == '"' || *s == '\'')
        {   
            symbol = symbol_checker(*s);
            s += 1;
            while(*s != symbol)
                s++;
        }
        while(*s == ' ')
        {
            if(!inside)
            {   
                inside = 0;
                spaces += 1;
            }
            s++;
        }
        s++;
    }
    return(spaces);
}
void echo_cmd(char **str,char *input)
{
    int i;
    int spaces;

    i = 1;
    spaces = space_checker(input); 
    while(str[i])
        printf("%s ",str[i++]);
    printf("\n");
}

void in_buit_cmd(char **str,char *input)
{
    if(!ft_strncmp(str[0],"echo",5))
        echo_cmd(str,input);
    else
        (printf("minishell: %s : command not found\n",str[0]),exit(EXIT_FAILURE));
}

void print_double(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {   
        printf("string %d: %s\n",i,str[i]);
        i++;
    }
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
            if(!ft_strncmp(input,"exit",5) || !ft_strncmp(input,"\"exit\"",7))
            {   
                printf("Exiting now.....");
                exit(EXIT_SUCCESS);
            }
            res = tokenization_char(input);
            // print_double(res);
            // in_buit_cmd(res,input);
            printf("spaces in the str: %d\n",space_checker(input));
            free(input);
            free_double(res);
        }
    }
    return 0;
}