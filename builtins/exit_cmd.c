#include "../minishell.h"

int valid_num(char *s)
{   
    int i;
    int len;

    i = 0;
    len = 0;
    if(s[i] == '+' || s[i] == '-')
        i++;
    while(s[i])
    {
        if(s[i] >= '0' && s[i] <= '9')
        {
            i++;
            len++;
        }
        else
            return (0);
    }
    return (len);
}

void error_msg(char *str)
{
    printf("exit\n");
    printf("minishell: exit: %s: numeric argument required\n",str);
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

void num_valid_check(unsigned long long exit_num, int check, unsigned long long lm, char *str)
{
    if(exit_num > LONG_MAX && check == 1)
        error_msg(str);
    else if(exit_num > lm && check == 0)
        error_msg(str);
}
void exit_cmd(t_path **paths, char **str)
{   
    unsigned long long exit_num;
    unsigned long long lm_check;
    int check;

    lm_check = (ULONG_MAX - LONG_MIN) + 1;
    check = 1;
    if(!ft_strncmp(str[0],"exit",5) && str[1] != NULL && str[2] != NULL)
    {
        (printf("exit\n"),printf("exit: too many arguments\n"));
        return ;
    }
    else if(!ft_strncmp(str[0],"exit",5) && str[1] != NULL)
    {   
        if(!valid_num(str[1]) || valid_num(str[1]) >= 20)
            error_msg(str[1]);
        exit_num = symbol_check(str[1],&check);
        num_valid_check(exit_num,check,lm_check,str[1]);
        if(!check)
            neg_num_exit(paths,exit_num);
        if(exit_num >= 256 && check == 1)
            exit_num = exit_num % 256;
        (ft_lstclear(paths),printf("exit\n"),exit(exit_num));
    }
    else if(!ft_strncmp(str[0],"exit",5) && str[1] == NULL)
        (ft_lstclear(paths),printf("exit\n"),exit(EXIT_SUCCESS));
}

