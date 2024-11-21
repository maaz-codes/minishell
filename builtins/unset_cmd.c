#include "../minishell.h"

void unset_cmd(char **str)
{
    if(str[1] == NULL)
        printf("unset: not enough arguments");
}