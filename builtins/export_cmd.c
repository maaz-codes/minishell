#include "../minishell.h"

void export_cmd(char **str, t_path **paths)
{
    if(!ft_strncmp("export",str[0],6) && str[1] == NULL)
        env_cmd(str, paths);
    if(!ft_strncmp("export",str[0],6) && str[1] != NULL)
        printf("working properly\n");
}