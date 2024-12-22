#include "minishell.h"

char  *signal_checkpoint(t_std_fds *std_fds, t_ancient *ancient_one)
{
    char *input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
    input = readline("minishell> ");
    if(!input)
    {
        write(1, "exit\n", 6);
		reset_std_fds(std_fds);
		mini_fuk(ancient_one, FREE_PATH);
        exit(EXIT_SUCCESS);
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

