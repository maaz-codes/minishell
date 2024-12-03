#include "minishell.h"

static void handle_sigint(int sig)
{
    if (sig == SIGINT)
	{   
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
        rl_replace_line("",0);
		rl_redisplay();
        signals.sig_int = 1;
	}
}

static void handle_sigquit()
{
    struct sigaction set;
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = SIG_IGN;
    sigaction(SIGQUIT,&set,NULL);
    signals.sig_quit = 0;
}

void set_signals()
{
    struct sigaction set;

    handle_sigquit(signals);
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = &handle_sigint;
    sigaction(SIGINT,&set,NULL);
}

void int_signals()
{
    signals.sig_int = 0;
    signals.sig_quit = 0;
    signals.pid = 0;
    signals.exit_status = 0;
}

