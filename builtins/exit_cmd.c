#include "../minishell.h"

int valid_num(char *s)
{   
    int i;

    i = 0;
    while(s[i])
    {
        if(s[i] >= '0' && s[i] <= '9')
            i++;
        else
            return (0);
    }
    return (i);
}

void exit_cmd(t_path **paths, char **str)
{   
    int exit_num;

    if(!ft_strncmp(str[0],"exit",5) && str[1] != NULL && str[2] != NULL)
    {
        (printf("exit\n"),printf("exit: too many arguments\n"));
        return ;
    }
    else if(!ft_strncmp(str[0],"exit",5) && str[1] != NULL)
    {   
        if(!valid_num(str[1]) || valid_num(str[1]) >= 20)
        {   
            printf("exit\n");
            printf("minishell: exit: %s: numeric argument required\n",str[1]);
            exit(255);
        }
        exit_num = ft_atoi(str[1]);
        if(exit_num < 0 || exit_num >= 256)
            exit_num = exit_num % 256;
        (ft_lstclear(paths),printf("exit\n"),exit(exit_num));
    }
    else if(!ft_strncmp(str[0],"exit",5) && str[1] == NULL)
        (ft_lstclear(paths),printf("exit\n"),exit(EXIT_SUCCESS));
}

