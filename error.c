#include "minishell.h"

int	print_error(int code)
{
	if (code == ERR_FORMAT)
		write(2, "Error: Wrong format\n", 21);
	else if (code == ERR_EXECVE)
		write(2, "Error: Execve() failed\n", 24);
	else if (code == ERR_FILE)
		write(2, "Error: Wrong File\n", 19);
	return (0);
}

void	print_exit(int code)
{
	if (code == ERR_MALLOC)
		printf("Error: Malloc Failed!\n");
	else if (code == ERR_FORK)
		write(2, "Error: Fork() failed\n", 22);
	else if (code == ERR_PIPE)
		printf("Error: Pipe() failed\n");
	else if (code == ERR_CMD)
		printf("minishell: cmd not found\n"), exit(127);
	exit(EXIT_FAILURE);
}

void free_str(char **str)
{
    if (str && *str)
    {
        free(*str); 
        *str = NULL;
    }
}
