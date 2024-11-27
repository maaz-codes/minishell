#include "../minishell.h"

void free_double(char **s)
{
    int i;

    i = 0;
    if(!s || !s[0])
        return ;
    while(s[i])
        free(s[i++]);
    free(s);
}