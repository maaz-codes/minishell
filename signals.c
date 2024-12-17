#include "minishell.h"

void handle_sigint(int sig)
{
    if (sig == SIGINT)
	{   
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
        rl_replace_line("",0);
		rl_redisplay();
        signal_caught = SIGINT;
	}
}

void handle_sigquit()
{
    struct sigaction set;
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = SIG_IGN;
    sigaction(SIGQUIT,&set,NULL);
}

static void sig_newline(int sig)
{
    (void)signal;
    rl_on_new_line();
    signal_caught = SIGINT;
}

void set_signals_after(t_ancient *ancient_one)
{
    struct sigaction set;

    handle_sigquit();
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = &sig_newline;
    // set.sa_flags = SA_RESTART;
    sigaction(SIGINT,&set,NULL);
}



void set_signals(t_ancient *ancient_one)
{
    // struct sigaction set;

    // handle_sigquit();
    // ft_memset(&set,0,sizeof(set));
    // set.sa_handler = &handle_sigint;
    // sigaction(SIGINT,&set,NULL);
    signal(SIGINT,handle_sigint);
}


