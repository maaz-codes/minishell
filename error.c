#include "minishell.h"

void	print_error(int code)
{
	if (code == ERR_FORMAT)
		printf("Error: Wrong format\n");
}

void print_exit(int code)
{
    if (code == ERR_MALLOC)
		printf("Error: Malloc Failed!\n");
    exit(EXIT_FAILURE);
}