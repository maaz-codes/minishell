/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:22:14 by maakhan           #+#    #+#             */
/*   Updated: 2024/09/24 19:27:10 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *str, char *buff)
{
	free(str);
	free(buff);
	return (NULL);
}

static char	*reader(int fd, char *buff, char *str, int chars_read)
{
	char	*s;

	while ((!ft_strchr_gnl(str, '\n')) && chars_read > 0)
	{
		chars_read = read(fd, buff, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		if (chars_read == 0)
		{
			free(buff);
			return (str);
		}
		buff[chars_read] = '\0';
		s = str;
		str = ft_strjoin_gnl(str, buff);
		if (!str)
			return (ft_free(s, buff));
		free(s);
	}
	free(buff);
	return (str);
}

static char	*fetch_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i] = str[i];
	return (line);
}

static char	*update(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	ptr = ft_strdup_gnl(str + i);
	free(str);
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*str;
	char		*line;
	int			chars_read;

	chars_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	str = reader(fd, buff, str, chars_read);
	if (!str)
		return (NULL);
	line = fetch_line(str);
	str = update(str);
	return (line);
}
