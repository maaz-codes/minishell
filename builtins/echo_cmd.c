#include "../minishell.h"

int valid_dash_n(char *str)
{
    int i;

    i = 1;
    while(str[i] == 'n' && str[i])
        i++;
    if(ft_strlen(str) == i)
        return (1);
    else
        return (0);

}

void n_check(int *checker, int *i,char **str)
{   
    *checker = 1;
    while(str[*i])
    {
        if(valid_dash_n(str[*i])) 
            *i += 1;
        else
            break;
    }
}

void echo_cmd(char **str, t_ancient *ancient_one)
{   
    int i; 
    int checker;

    checker = 0;
    i = 1;
    if(!ft_strncmp(str[0],"echo",5))
    {   
        if(str[1] == NULL)
            checker = 1;
        else if(valid_dash_n(str[1]))
            n_check(&checker, &i, str);
    }
    while(str[i])
    {   
        if(!ft_strncmp(str[i],"$?",2))
            printf("exit_status: %d",ancient_one->exit_status);
        else
            printf("%s",str[i]);
        if(str[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if(!checker)
        printf("\n");
}
