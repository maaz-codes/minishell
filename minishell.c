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

void in_buit_cmd(char **str,t_path **paths, char **env)
{   
    if(!str[0])
        return ;
    if(!ft_strncmp(str[0],"echo",5))
        echo_cmd(str);
    else if(!ft_strncmp(str[0],"pwd",4))
        pwd_cmd(str);
    else if(!ft_strncmp(str[0],"cd",3))
        cd_cmd(str,paths,env);
    else if (!ft_strncmp(str[0],"exit",5))
        exit_cmd(paths,str);
    else if(!ft_strncmp(str[0],"env",4))
        env_cmd(str, env);
    else
        (printf("minishell: %s : command not found\n",str[0]));
}

char *get_cwd(void)
{
    char cwd[1024];
    char *res;
    if(getcwd(cwd,sizeof(cwd)) == NULL)
        printf("error");
    res = new_path(cwd,0);
    return(res);
}

t_path	*int_cd(void)
{
	t_path	*node_new;
    char    *str1;
    char    *str2;

    str1 = get_cwd();
    str2 = get_cwd();
	node_new = (t_path *)malloc(sizeof(t_path));
	if (node_new == NULL)
		return (NULL);
	node_new->pwd = str1;
	node_new->pwd_old = str2;
	node_new->next = NULL;
	return (node_new);
}

int main(int ac, char **av, char **env)
{   
    t_path *paths;

    paths = int_cd();
    
    while(1)
    {
        char *input;
        char **res;


        set_signals();
        input = readline("minishell> ");
        set_signals_after();
        if(input) 
        {   
            res = tokenization_char(input);
            add_history(input);
            free(input);
            in_buit_cmd(res,&paths,env);
            free_double(res);
        }
    }
    return 0;
}