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

static void handle_sigquit(void)
{
    struct sigaction set;
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = SIG_IGN;
    sigaction(SIGQUIT,&set,NULL);
}

static void sig_newline(int signal)
{
    (void)signal;
    rl_on_new_line();
}
void set_signals_after(void)
{
    struct sigaction set;

    ft_memset(&set,0,sizeof(set));
    set.sa_handler = &sig_newline;
    sigaction(SIGQUIT, &set, NULL);
    sigaction(SIGINT, &set, NULL);
}

void set_signals(void)
{
    struct sigaction set;

    handle_sigquit();
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = &handle_sigint;
    sigaction(SIGINT,&set,NULL);
}