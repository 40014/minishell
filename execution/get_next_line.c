/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:51:09 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 16:51:11 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_rest(char *line, int j)
{
	char	*rest;
	int		i;
	int		t;

	i = 0;
	t = j;
	if (line[j] == '\0' || line[j + 1] == '\0')
		return (NULL);
	while (line[j + 1] != '\0')
	{
		j++;
		i++;
	}
	rest = (char *)ft_calloc(i + 1, 1);
	if (!rest)
		return (NULL);
	i = 0;
	while (line[t + 1] != '\0')
	{
		rest[i] = line[t + 1];
		t++;
		i++;
	}
	return (rest);
}

char	*ft_seperate_rest(char *line, int c, int i, int j)
{
	char	*last;

	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (c == 1)
	{
		last = get_rest(line, i);
		return (free(line), last);
	}
	if (line[i] == '\0')
	{
		last = (char *)ft_calloc(i + 1, 1);
		if (!last)
			return (NULL);
	}
	else
	{
		last = (char *)ft_calloc(i + 2, 1);
		if (!last)
			return (NULL);
		last[i] = '\n';
	}
	while (j++ < i)
		last[j - 1] = line[j - 1];
	return (last);
}

char	*ft_fill_buf(int fd, char *str, ssize_t b)
{
	char	*tmp;
	char	*buf;

	while (b > 0)
	{
		buf = (char *)ft_calloc((size_t)BUFFER_SIZE + 1, 1);
		if (!buf)
			return (NULL);
		b = read(fd, buf, BUFFER_SIZE);
		if (b == -1)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		tmp = str;
		str = ft_strjoin(tmp, buf, 1, 1);
		free(tmp);
		free(buf);
		if (ft_strchr(str, '\n') == 1)
			break ;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (!str)
	{
		str = (char *)ft_calloc(1, 1);
		if (!str)
			return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0
		|| BUFFER_SIZE > INT_MAX)
		return (free(str), str = NULL, NULL);
	str = ft_fill_buf(fd, str, 1);
	if (str[0] == '\0')
		return (free(str), str = NULL, NULL);
	line = ft_seperate_rest(str, 5, 0, 0);
	str = ft_seperate_rest(str, 1, 0, 0);
	return (line);
}
