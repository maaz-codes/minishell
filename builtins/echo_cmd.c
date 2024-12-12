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

void n_check(int *checker, int *i,char *str)
{
    if(!ft_strncmp(str,"-n",2))
        *checker = valid_dash_n(str);
    if(*checker == 1)
        *i += 1;
}
void echo_cmd(char **str, t_ancient *ancient_one)
{   
    int i; 
    int checker;
    int valid_n;

    checker = 0;
    i = 1;
    if(!ft_strncmp(str[0],"echo",5) && str[1] == NULL)
    {
        printf("\n");
        return ;
    }
    else if(!ft_strncmp(str[0],"echo",5) && !ft_strncmp(str[i],"-n",3) && str[i + 1] == NULL)
        return ;
    if(!ft_strncmp(str[i],"$?",2))
    {
        printf("exit_status: %d\n",ancient_one->exit_status);
        return ;
    }
    n_check(&checker,&i,str[i]);
    while(str[i])
    {
        printf("%s",str[i]);
        if(str[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if(!checker)
        printf("\n");
}
