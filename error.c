#include "minishell.h"

int	print_error(int code)
{
	if (code == ERR_FORMAT)
		printf("Error: Wrong format\n");
	else if (code == ERR_FORK)
		printf("Error: Fork() failed\n");
	else if (code == ERR_EXECVE)
		printf("Error: Execve() failed\n");
	return (0);
}

void print_exit(int code)
{
    if (code == ERR_MALLOC)
		printf("Error: Malloc Failed!\n");
	else if (code == ERR_FILE)
		printf("Error: File Failed!\n");
    exit(EXIT_FAILURE);
}
