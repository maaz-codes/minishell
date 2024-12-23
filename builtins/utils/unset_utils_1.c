#include "../../minishell.h"

int	valid_unset(char *str)
{
	int	i;
	int	check;
	int	len;

	len = 1;
	check = 1;
	i = 0;
	if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
		|| str[i] == '_')
		i++;
	else
		check = 0;
	if (!check)
		return (0);
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_' || str[i] >= '0' && str[i] <= '9')
			len++;
		i++;
	}
	if (len != ft_strlen(str))
		check = 0;
	return (check);
}