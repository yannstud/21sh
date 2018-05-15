/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdeletting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:19:07 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:10 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		clear_right_del(t_line *line)
{
	size_t i;

	ft_putstr_fd(tgetstr("cb", NULL), 0);
	i = line->iline;
	while (i < ft_strlen(line->line) + 3)
	{
		ft_putstr_fd(tgetstr("le", NULL), 0);
		ft_putstr_fd(tgetstr("dc", NULL), 0);
		i++;
	}
}

void		write_del_line(char *str, t_line *line)
{
	size_t i;

	ft_putstr_fd("➜ ", 1);
	ft_putstr_fd(str, 1);
	i = ft_strlen(str);
	while (i > line->count)
	{
		ft_putstr_fd(tgetstr("le", NULL), 0);
		i--;
	}
}

void		right_del(t_line *line)
{
	char	buff[1];
	char	*str;
	size_t	i;
	size_t	j;

	read(0, buff, 1);
	if (line->line[0])
	{
		if (line->count != 0 && line->count == ft_strlen(line->line))
			return ;
		if (!(str = (char *)malloc(sizeof(char) * ft_strlen(line->line) + 1)))
			return ;
		left(ft_strlen(line->line) + 2);
		ft_memcpy(str, line->line, line->count);
		j = line->count;
		i = line->count + 1;
		while (line->line[i])
			str[j++] = line->line[i++];
		str[j] = '\0';
		free(line->line);
		line->line = str;
		print_prompt(0);
		ft_putstr_fd(line->line, 0);
		left2(line);
	}
}

void		clear_line(t_line *line)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line->line) + 2)
	{
		ft_putstr_fd(tgetstr("le", NULL), 0);
		ft_putstr_fd(tgetstr("dc", NULL), 0);
		i++;
	}
	i = ft_strlen(line->line);
	print_prompt(0);
	ft_putstr_fd(line->line, 0);
	line->count++;
	while (i-- > line->count)
		ft_putstr_fd(tgetstr("le", NULL), 0);
}

void		simple_clear_line(t_line *line)
{
	size_t	i;

	i = 0;
	if (line->line)
	{
		while (i < ft_strlen(line->line))
		{
			ft_putstr_fd(tgetstr("le", NULL), 0);
			i++;
		}
		ft_putstr_fd(tgetstr("cd", NULL), 0);
	}
}
