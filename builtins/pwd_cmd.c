#include "../minishell.h"

void pwd_cmd(char **str)
{
    char cwd[1024];

    if(str[1] != NULL)
    {
        printf("pwd: too many arguments\n");
        return ;
    }
    if(getcwd(cwd,sizeof(cwd)) != NULL)
        printf("%s\n",cwd);
    else
        printf("error");
}
