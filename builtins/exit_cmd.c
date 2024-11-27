#include "../minishell.h"

void error_msg(char *str,t_path **paths)
{
    printf("exit\n");
    printf("minishell: exit: %s: numeric argument required\n",str);
    ft_lstclear(paths);
    exit(255);
}

void neg_num_exit(t_path **paths, unsigned long long exit_num)
{   
    long negative_num;

    negative_num = -exit_num;
    negative_num = negative_num % 256;
    (ft_lstclear(paths),printf("exit\n"),exit(negative_num));
}

unsigned long long symbol_check(char *str, int *check)
{   
    unsigned long long exit_num;
    if(str[0] == '-')
    {   
        exit_num = ft_atol(str + 1);
        *check = 0;
    }
    else
        exit_num = ft_atol(str);
    return (exit_num);
}

void num_valid_check(unsigned long long e, int c, char *str, t_path **paths)
{
    if(e > LONG_MAX && c == 1)
        error_msg(str,paths);
    else if(e > (ULONG_MAX - LONG_MIN) + 1 && c == 0)
        error_msg(str,paths);
}
void exit_cmd(t_path **paths, char **str)
{   
    unsigned long long exit_num;
    int check;

    check = 1;
    if(!ft_strncmp(str[0],"exit",5) && str[1] != NULL && str[2] != NULL)
    {
        (printf("exit\n"),printf("exit: too many arguments\n"));
        return ;
    }
    else if(!ft_strncmp(str[0],"exit",5) && str[1] != NULL)
    {   
        valid_num(str[1],paths);
        exit_num = symbol_check(str[1],&check);
        num_valid_check(exit_num,check,str[1],paths);
        if(!check)
            neg_num_exit(paths,exit_num);
        if(exit_num >= 256 && check == 1)
            exit_num = exit_num % 256;
        (ft_lstclear(paths),printf("exit\n"),exit(exit_num));
    }
    else if(!ft_strncmp(str[0],"exit",5) && str[1] == NULL)
        (ft_lstclear(paths),printf("exit\n"),exit(EXIT_SUCCESS));
}

