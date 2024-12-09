#include "minishell.h"

static void handle_sigint(int sig)
{
    if (sig == SIGINT)
	{   
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
        rl_replace_line("",0);
		rl_redisplay();
        exit_status = 1;
	}
}

static void handle_sigquit()
{
    struct sigaction set;
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = SIG_IGN;
    set.sa_flags = SA_RESTART;
    sigaction(SIGQUIT,&set,NULL);
    exit_status = 0;
}

void set_signals()
{
    struct sigaction set;

    handle_sigquit();
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = &handle_sigint;
    set.sa_flags = SA_RESTART;
    sigaction(SIGINT,&set,NULL);
}


