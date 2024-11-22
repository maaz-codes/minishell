#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "minishell.h"

int main(void)
{   
    
    char *test;

    test = malloc(1);
    test = " ";

    // printf("print test-%s-\n",test);
    if(chdir(test) == -1)
    {
        printf("not valid\n");
    }
    else
        printf("valid\n");
}