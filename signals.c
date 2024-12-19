#include "minishell.h"

char  *signal_checkpoint(t_std_fds *std_fds, t_ancient *ancient_one)
{
    char *input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
    input = readline("minishell> ");
    if(!input)
    {
        printf("\nexiting now...\n");
		reset_std_fds(std_fds);
		mini_fuk(ancient_one, FREE_PATH);
        exit(127);
    }
	if(signal_caught == SIGINT)
		ancient_one->exit_status = 1;
    else if(signal_caught == 127)
        ancient_one->exit_status = 127;
	else if(signal_caught == 0)
		ancient_one->exit_status = 0;
	if(*input != '\0')
		signal_caught = 0;
    return (input);
}

void handle_sigint(int sig)
{
    if (sig == SIGINT)
	{   
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
        // rl_replace_line("",0);
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
