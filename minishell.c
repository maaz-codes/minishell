#include "minishell.h"

t_sig signals;

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
        env_cmd(str, paths);
    else if(!ft_strncmp(str[0],"unset",6))
        unset_cmd(str,paths);
    else if(!ft_strncmp(str[0],"export",7))
        export_cmd(str,paths);
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

char  *signal_checkpoint()
{
    char *input;

    int_signals();
    set_signals();
    input = readline("minishell> ");
    if(!input)
    {
        printf("\nexiting now...\n");
        exit(signals.exit_status);
    }
    return (input);
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

        input = signal_checkpoint();
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
