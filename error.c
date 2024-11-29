#include "minishell.h"

int	print_error(int code)
{
	if (code == ERR_FORMAT)
		printf("Error: Wrong format\n");
	else if (code == ERR_FORK)
		printf("Error: Fork() failed\n");
	else if (code == ERR_EXECVE)
		printf("Error: Execve() failed\n");
	else if (code == ERR_FILE)
		printf("Error: Wrong File\n");
	return (0);
}

void	print_exit(int code)
{
	if (code == ERR_MALLOC)
		printf("Error: Malloc Failed!\n");
	else if (code == ERR_FILE)
		printf("Error: File Failed!\n");
	else if (code == ERR_FORK)
		printf("Error: Fork() failed\n");
	else if (code == ERR_PIPE)
		printf("Error: Pipe() failed\n");
	else if (code == ERR_CMD)
		printf("minishell: cmd not found\n"), exit(127);
	exit(EXIT_FAILURE);
}
