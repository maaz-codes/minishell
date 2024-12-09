#include "minishell.h"

static void handle_sigint(int sig)
{
    if (sig == SIGINT)
	{   
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
        rl_replace_line("",0);
		rl_redisplay();
	}
}

static void handle_sigquit()
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
}

void set_signals_after()
{
    struct sigaction set;

    handle_sigquit();
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = &sig_newline;
    set.sa_flags = SA_RESTART;
    sigaction(SIGINT,&set,NULL);
}

void sigint_catch_doc(int sig)
{
    if(sig == SIGINT)
    {
        signal_caught = SIGINT;
    }
}

void set_signals_heredoc()
{
    struct sigaction set;

    handle_sigquit();
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = &sigint_catch_doc;
    sigemptyset(&set.sa_mask);
    sigaction(SIGINT,&set,NULL);
}

void set_signals()
{
    struct sigaction set;

    handle_sigquit();
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = &handle_sigint;
    sigaction(SIGINT,&set,NULL);
}


