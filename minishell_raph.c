#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


void in_buit_cmd(char **str,t_path **paths, char **env)
{   
    if(!str[0])
        return ;
    if(!ft_strncmp(str[0],"echo",5))
        echo_cmd(str);
    else if(!ft_strncmp(str[0],"pwd",4))
        pwd_cmd(str);
    else if(!ft_strncmp(str[0],"cd",3))
        cd_cmd(str,paths);
    else if (!ft_strncmp(str[0],"exit",5))
        exit_cmd(paths,str);
    else if(!ft_strncmp(str[0],"env",4))
        env_cmd(str, paths);
    else if(!ft_strncmp(str[0],"unset",6))
        unset_cmd(str,paths);
    else if(!ft_strncmp(str[0],"export",7))
        export_cmd(str,paths);
    else
        (printf("minishell: %s : command not found\n",str[0]));
}

int main(int ac, char **av, char **env)
{   
    t_path *paths;

    paths = int_cd();
    paths->env_struct = int_env(env);
    paths->exp_struct = int_exp(env);
    while(1)
    {
        char *input;
        char **res;

        // set_signals();
        input = readline("minishell> ");
        // set_signals_after();
        if(!input)
        {
            printf("\nexiting now...\n");
            exit(0);
        }
        if(input) 
        {   
            res = tokenization_char(input);
            add_history(input);
            free(input);
            in_buit_cmd(res,&paths,env);
            free_double(res);
        }
    }
}
