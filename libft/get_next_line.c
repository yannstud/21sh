/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:10:38 by ysalaun           #+#    #+#             */
/*   Updated: 2018/01/25 21:25:28 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*get_buffer(char *buffer, int fd, int *ret)
{
	char	str[BUFF_SIZE + 1];

	ft_bzero(str, BUFF_SIZE);
	if ((*ret = read(fd, str, BUFF_SIZE)) == -1)
		return (NULL);
	str[*ret] = '\0';
	if (buffer == NULL)
	{
		if (!(buffer = ft_strdup(str)))
			return (NULL);
	}
	else
	{
		if (!(buffer = ft_strjoin(buffer, str)))
			return (NULL);
	}
	return (buffer);
}

static int		last_line(char *buffer, char **line)
{
	int		i;

	if (buffer[0] != '\0')
	{
		i = -1;
		if (!((*line) = ft_strnew(ft_strlen(buffer))))
			return (0);
		while (buffer[++i] != '\0')
			(*line)[i] = buffer[i];
		(*line)[i] = '\0';
		i = -1;
		while (buffer[++i])
			buffer[i] = '\0';
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_str	str;
	t_gnl			gnl;

	if (line == NULL || fd <= -1)
		return (-1);
	gnl.ret = 1;
	while (gnl.ret > 0)
	{
		if (!(str.buffer = get_buffer(str.buffer, fd, &gnl.ret)))
			return (-1);
		ft_memdel((void *)&str.tmp);
		str.tmp = str.buffer;
		if ((gnl.str = ft_strchr(str.buffer, '\n')))
		{
			gnl.i = -1;
			*line = ft_strnew(ft_strlen(str.buffer));
			while (str.buffer[++gnl.i] != '\n')
				(*line)[gnl.i] = str.buffer[gnl.i];
			str.tmp = str.buffer;
			str.buffer = gnl.str + 1;
			return (1);
		}
	}
	return (last_line(str.buffer, line));
}
