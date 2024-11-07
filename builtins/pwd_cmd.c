#include "../minishell.h"

void pwd_cmd(void)
{
    char cwd[1024];
    int i = 0;
    if(getcwd(cwd,sizeof(cwd)) != NULL)
        printf("%s\n",cwd);
    else
        printf("error");

    while(cwd[i])
        i++;
}
