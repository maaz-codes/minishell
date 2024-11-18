#include "minishell.h"

int	print_error(int code)
{
	if (code == ERR_FORMAT)
		printf("Error: Wrong format\n");
	if (code == ERR_FORK)
		printf("Error: Fork failed\n");
	return (0);
}

void print_exit(int code)
{
    if (code == ERR_MALLOC)
		printf("Error: Malloc Failed!\n");
    exit(EXIT_FAILURE);
}
