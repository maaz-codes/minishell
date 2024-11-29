#include "../minishell.h"

void clear_all(t_path **paths,char **str)
{   
    t_exp *exp;
    t_env *env;

    exp = (*paths)->exp_struct;
    env = (*paths)->env_struct;
    if(str)
        free_double(str);
    if(env)
        ft_lstclear_env(&env);
    if(exp)
        ft_lstclear_exp(&exp);
    if((*paths))
        ft_lstclear_path(&(*paths));
    return ;
}

void error_msg(char **str,t_path **paths)
{
    printf("exit\n");
    printf("minishell: exit: %s: numeric argument required\n",str[1]);
    clear_all(paths,str);
    exit(255);
}

void neg_num_exit(t_path **paths, char **str, unsigned long long exit_num)
{   
    long negative_num;

    negative_num = -exit_num;
    negative_num = negative_num % 256;
    (clear_all(paths,str),printf("exit\n"),exit(negative_num));
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

void num_valid_check(unsigned long long e, int c, char **str, t_path **paths)
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
        valid_num(str[1],paths,str);
        exit_num = symbol_check(str[1],&check);
        num_valid_check(exit_num,check,str,paths);
        if(!check)
            neg_num_exit(paths,str,exit_num);
        if(exit_num >= 256 && check == 1)
            exit_num = exit_num % 256;
        (clear_all(paths,str),printf("exit\n"),exit(exit_num));
    }
    else if(!ft_strncmp(str[0],"exit",5) && str[1] == NULL)
        (clear_all(paths,str),printf("exit\n"),exit(exit_num));
}

