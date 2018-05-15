/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursormoove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:23:09 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:17 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		curs_left(t_line *line)
{
	if (line->count > 0)
	{
		ft_putstr_fd(tgetstr("le", NULL), 0);
		line->count--;
	}
	return ;
}

void		going_right(t_line *line)
{
	if ((line->count + 4) % line->icol == 0)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		line->count++;
		return ;
	}
	else if ((line->count + 4) % line->icol < line->icol)
	{
		ft_putstr_fd(tgetstr("nd", NULL), 0);
		line->count++;
	}
}

void		opt_high(t_line *line)
{
	size_t i;

	if (line->count > line->icol)
	{
		i = 0;
		while (i < line->icol)
		{
			curs_left(line);
			i++;
		}
	}
}

void		opt_down(t_line *line)
{
	size_t i;

	if (line->line)
	{
		i = 0;
		while (i < line->icol)
		{
			curs_right(line);
			i++;
		}
	}
}

void		opt_left_right(t_line *line)
{
	char ret[1];

	ft_bzero(ret, 1);
	read(0, ret, 1);
	if (ret[0] == 67)
		return (opt_right(line));
	else if (ret[0] == 68)
		return (opt_left(line));
	else if (ret[0] == 65)
		return (opt_high(line));
	else if (ret[0] == 66)
		return (opt_down(line));
}
