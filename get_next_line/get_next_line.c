/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:00:19 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/01/22 11:44:05 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*first_line(char *str)
{
	int		c;
	char	*new_str;

	c = 0;
	if (!str)
		return (free(str), NULL);
	while (str[c] && str[c] != '\n')
		c++;
	if (str[c] && str[c] == '\n')
		c++;
	new_str = (char *)malloc(sizeof(char) * (c + 1));
	if (!new_str)
		return (NULL);
	c = 0;
	while (str[c] && str[c] != '\n')
	{
		new_str[c] = str[c];
		c++;
	}
	if (str[c] && str[c] == '\n')
		new_str[c++] = '\n';
	new_str[c] = 0;
	return (new_str);
}

static	char	*set_tmp(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	tmp = ft_g_strdup(str + i, 0);
	free(str);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*print_line(char *str, char *buf, int fd, int i)
{
	static char	*tmp;
	char		*line;

	if (tmp)
		str = ft_g_strdup(tmp, 1);
	while (i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
			return (free(buf), NULL);
		buf[i] = '\0';
		str = ft_g_strjoin(str, buf);
		if (!str || !*str)
			return (free(buf), free(str), NULL);
		if (ft_strchr(str, '\n'))
			break ;
		ft_bzero(buf, i);
	}
	line = first_line(str);
	tmp = set_tmp(str);
	return (free(buf), line);
	if (i < 0)
		return (free(buf), NULL);
}

char	*get_next_line(int fd)
{
	char			*buf;
	char			*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	buf = NULL;
	buf = (char *)malloc(sizeof (char) * BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	str = NULL;
	return (print_line(str, buf, fd, 1));
}
