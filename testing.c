#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "minishell.h"

int main(int ac,char **av)
{
    (void)ac;
    int exit_num;

    if(!ft_strncmp(av[1],"exit",5) && av[2] != NULL)
    {
        printf("exit func\n");
        exit_num = ft_atoi(av[2]);
        printf("exit num: %d\n",exit_num);
        if(!exit_num)
        {
            printf("bruh\n");
            exit(255);
        }
        else
            exit(exit_num);
    }
}