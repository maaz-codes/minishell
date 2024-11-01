#include "minishell.h"

void echo_cmd(char **str,char *input)
{   
    int i; 
    
    i = 1;
    while(str[i])
        printf("%s ",str[i++]);
    printf("\n");
   
}