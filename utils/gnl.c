/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 14:10:54 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:59:01 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int		get_line_len(char **rest)
{
	int	i;

	i = 0;
	while ((*rest)[i] != '\n')
		i++;
	i++;
	return (i);
}

int		check_read(char **rest, char **line)
{
	int		i;
	char	*tmp;
	int		len;

	i = 0;
	len = ft_strlen(*rest);
	if (!(*line = malloc(sizeof(char) * get_line_len(&(*rest)))))
		return (-1);
	while ((*rest)[i])
	{
		if ((*rest)[i] == '\n')
		{
			(*line)[i] = '\0';
			if (!(tmp = ft_strdup(*rest)))
				return (-1);
			free(*rest);
			if (!(*rest = ft_strsub(tmp, i + 1, len - i)))
				return (-1);
			free(tmp);
			return (1);
		}
		(*line)[i] = (*rest)[i];
		i++;
	}
	return (0);
}

int		last_line(char **rest, char **line)
{
	int i;

	i = 0;
	if (!ft_strlen(*rest))
		return (0);
	if (!(*line = malloc(sizeof(char) * ft_strlen(*rest) + 1)))
		return (-1);
	while ((*rest)[i])
	{
		(*line)[i] = (*rest)[i];
		i++;
	}
	(*line)[i] = '\0';
	free(*rest);
	*rest = NULL;
	return (1);
}

int		ft_read(char **rest, char *str, char **line)
{
	char *tmp;

	if (!*rest)
	{
		if (!(*rest = ft_strdup(str)))
			return (-1);
	}
	else
	{
		if (!(tmp = ft_strdup(*rest)))
			return (-1);
		free(*rest);
		if (!(*rest = ft_strjoin(tmp, str)))
			return (-1);
		free(tmp);
	}
	ft_bzero(str, BUFF_SIZE + 1);
	if ((ft_strchr(*rest, '\n')))
		return (check_read(&*rest, line));
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*rest;
	char		str[BUFF_SIZE + 1];
	int			reader;
	int			end;
	int			res;

	end = 0;
	ft_bzero(str, BUFF_SIZE + 1);
	if (fd < 0 || !line)
		return (-1);
	while (((reader = read(fd, str, BUFF_SIZE)) > 0) || !end)
	{
		res = ft_read(&rest, str, line);
		if (res == 1)
			return (1);
		else if (res == -1)
			return (-1);
		end = 1;
	}
	if (reader < 0)
		return (-1);
	return (last_line(&rest, line));
	return (0);
}
