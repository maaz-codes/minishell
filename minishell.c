#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void free_double(char **s)
{
    int i;

    i = 0;
    if(!s || !s[0])
        return ;
    while(s[i])
        free(s[i++]);
    free(s);
}

void exit_cmd(void)
{
    printf("Exiting now.....");
    exit(EXIT_SUCCESS);
}

void in_buit_cmd(char **str,t_path **paths)
{
    if(!ft_strncmp(str[0],"echo",5))
        echo_cmd(str);
    else if(!ft_strncmp(str[0],"pwd",4))
        pwd_cmd();
    else if(!ft_strncmp(str[0],"cd",3))
        cd_cmd(str,paths);
    else if (!ft_strncmp(str[0],"exit",5))
        exit_cmd();
    else
        (printf("minishell: %s : command not found\n",str[0]));
}

void print_double(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {   
        printf("string %d: %s\n",i,str[i]);
        i++;
    }
}

int main(int ac, char **av, char **envp)
{   
    while(1)
    {
        char *input;
        char **res;
        t_path *paths;

        paths = malloc(sizeof(t_path));
        input = readline("minishell> ");

        if(input) 
        {   
            res = tokenization_char(input);
            in_buit_cmd(res,&paths);
            add_history(input);
            free(input);
            free_double(res);
        }
    }
    return 0;
}