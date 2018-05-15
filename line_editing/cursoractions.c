/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursoractions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:19:50 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:18 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		go_home(t_line *line)
{
	size_t			i;
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	i = 0;
	if (ft_strlen(line->line) < (ws.ws_row - 1) * (ws.ws_col - 1))
	{
		while (i < line->count)
		{
			ft_putstr_fd(tgetstr("le", NULL), 0);
			i++;
		}
		line->count = 0;
	}
}

void		go_end(t_line *line)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (ft_strlen(line->line) < (ws.ws_row - 1) * (ws.ws_col - 1))
	{
		while (line->count != ft_strlen(line->line))
			going_right(line);
	}
}

void		opt_right(t_line *line)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (ft_strlen(line->line) < (ws.ws_row - 1) * (ws.ws_col - 1))
	{
		while (line->count < ft_strlen(line->line) &&
			line->line[line->count] == ' ')
			going_right(line);
		while (line->count < ft_strlen(line->line) &&
			line->line[line->count] != ' ')
			going_right(line);
	}
}

void		opt_left(t_line *line)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (ft_strlen(line->line) < (ws.ws_row - 1) * (ws.ws_col - 1))
	{
		while (line->count > 0 && line->line[line->count - 1] == ' ')
		{
			ft_putstr_fd(tgetstr("le", NULL), 0);
			line->count--;
		}
		while (line->count > 0 && line->line[line->count - 1] != ' ')
		{
			ft_putstr_fd(tgetstr("le", NULL), 0);
			line->count--;
		}
	}
}

void		curs_right(t_line *line)
{
	if (line->line)
	{
		if (line->count < ft_strlen(line->line))
			going_right(line);
	}
}
