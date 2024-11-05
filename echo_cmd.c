#include "minishell.h"

void echo_cmd(char **str)
{   
    int i; 
    int checker;

    checker = 0;
    i = 1;
    if(!ft_strncmp(str[i],"-n",3))
    {
        i++;
        checker = 1;
    }
    while(str[i])
    {
        printf("%s",str[i]);
        if(str[i + 1] != NULL)
            printf(" ");
        i++;
    }
    
    if(!checker)
        printf("\n");
}