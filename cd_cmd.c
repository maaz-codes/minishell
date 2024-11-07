#include "minishell.h"

void ft_append(t_path **paths, char *cwd)
{
    t_path *new_node;
    t_path *last_node;
    
}
void cd_cmd(char **str, t_path **paths)
{
    char cwd[1024];
    if(getcwd(cwd,sizeof(cwd)) != NULL)
        printf("%s\n",cwd);
    else
        printf("error\n");

    
}