/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:30:51 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:20 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		del_carac(t_line *line)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(line->line))))
		return ;
	line->count--;
	ft_putstr_fd(tgetstr("le", NULL), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_memcpy(str, line->line, line->count);
	i = line->count + 1;
	j = line->count;
	while (line->line[i])
	{
		ft_putchar_fd(line->line[i], 0);
		str[j++] = line->line[i++];
	}
	str[j] = '\0';
	free(line->line);
	line->line = str;
	i = ft_strlen(line->line) + 1;
	while (--i > line->count)
		ft_putstr_fd(tgetstr("le", NULL), 0);
}

int			del_left(t_line *line)
{
	if (line->count > 0)
	{
		if (line->count == ft_strlen(line->line))
		{
			line->count--;
			line->line[line->count] = '\0';
			ft_putstr_fd(tgetstr("le", NULL), 0);
			ft_putstr_fd(tgetstr("dc", NULL), 0);
		}
		else
			del_carac(line);
	}
	return (1);
}

void		insert_inline(t_line *line, char c)
{
	size_t			i;
	size_t			j;
	char			*str;
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (line->line)
	{
		if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(line->line) + 2))))
			return ;
		i = 0;
		while (i < line->count)
		{
			str[i] = line->line[i];
			i++;
		}
		j = i;
		str[i++] = c;
		while (line->line[j])
			str[i++] = line->line[j++];
		str[i] = '\0';
		free(line->line);
		line->line = str;
		clear_line(line);
	}
}
