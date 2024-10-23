/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_modif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:50:58 by rcreer            #+#    #+#             */
/*   Updated: 2024/10/23 17:20:01 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	safe_malloc(char **token_v, int position, size_t length)
{
	int	i;

	i = 0;
	token_v[position] = malloc(length);
	if (token_v[position] == NULL)
	{
		while (i < position)
		{
			free(token_v[i]);
			i++;
		}
		free(token_v);
		return (1);
	}
	return (0);
}

int	fill(char **token_v, char const *s, char del)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == del && *s)
			++s;
		while (*s != del && *s)
		{
			++len;
			++s;
		}
		if (len)
		{
			if (safe_malloc(token_v, i, len + 1))
				return (1);
			ft_strlcpy(token_v[i], s - len, len + 1);
			token_v[i][len] = '\0';
		}
		++i;
	}
	return (0);
}

size_t	count_tokens(char const *s, char del)
{
	size_t	tokens;
	int		inside;

	tokens = 0;
	while (*s)
	{
		inside = 0;
		while (*s == del && *s)
			++s;
		while (*s != del && *s)
		{
			if (!inside)
			{
				++tokens;
				inside = 1;
			}
			++s;
		}
	}
	return (tokens);
}
int checker(char *s)
{
    int i = 0;
    int inside = 0;
    
    while(s[i])
    {	
		inside = 0;
		while(s[i] == ' ')
			i++;
		while(s[i] == '"')
		{
			if(!inside)
			{
				printf("%c\n",s[i]);
				inside = 1;
			}
			i++; 
		}
		i++;
    }
    if(inside == 0)
        return 1;
    else
        return 0;
}

char	**split_modif(char *s, char c)
{
	char	**token_v;
	int		token;
	int		check_valid;

	if (s == NULL)
		return (NULL);
	token = 0;
	check_valid = checker(s);
	token = count_tokens(s, c);
	token_v = (char **)malloc(sizeof(char *) * (token + 1));
	if (token_v == NULL)
		return (NULL);
	token_v[token] = NULL;
	if (fill(token_v, s, c))
		return (NULL);
	return (token_v);
}

// int main(int ac, char **av)
// {	
// 	printf("check: %d\n",checker(av[1]));
// }
