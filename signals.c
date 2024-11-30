#include "minishell.h"

static void handle_sigint(int sig)
{
    if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
        // rl_replace_line("",0);
		rl_redisplay();
	}
}

static void handle_sigquit(t_sig sig)
{
    struct sigaction set;
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = SIG_IGN;
    sigaction(SIGQUIT,&set,NULL);
    sig.sig_quit = 0;
}

static void sig_newline(int signal)
{
    (void)signal;
    rl_on_new_line();
}
void set_signals_after(t_sig signals)
{
    struct sigaction set;

    ft_memset(&set,0,sizeof(set));
    set.sa_handler = &sig_newline;
    sigaction(SIGQUIT, &set, NULL);
    sigaction(SIGINT, &set, NULL);
}

void set_signals(t_sig signals)
{
    struct sigaction set;

    handle_sigquit(signals);
    ft_memset(&set,0,sizeof(set));
    set.sa_handler = &handle_sigint;
    printf("signal: %d\n",sigaction(SIGINT,&set,NULL));
}

void int_signals(t_sig signals)
{
    signals.sig_int = 0;
    signals.sig_quit = 0;
    signals.pid = 0;
    signals.exit_status = 0;
}

