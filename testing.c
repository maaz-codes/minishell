#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "minishell.h"

static void handle_sigint(int sig)
{
    if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
        rl_replace_line("",0);
		rl_redisplay();
        // signals.sig_int = 1;
	}
}

int main(int ac, char **av, char **env)
{   
    struct sigaction set;
    set.sa_handler = &handle_sigint;
    if(!sigaction(SIGINT,&set,NULL));
        printf("sigint\n");
}