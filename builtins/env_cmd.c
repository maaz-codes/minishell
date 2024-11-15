#include "../minishell.h"

void env_cmd(char **str, char **env)
{   
    if(str[1] != NULL)
    {
        printf("env: too many arguments\n");
        return ;
    }
    while(*env)
    {
        printf("%s\n",*env);
        env++;
    }
}