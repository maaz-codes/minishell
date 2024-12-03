#include "../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*hold;
	size_t	i;

	hold = b;
	i = 0;
	while (i < len)
	{
		*(char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (hold);
}
