/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 06:16:13 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:59 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		ft_strlinecat(t_line *line)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (line && line->line)
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
		str[i++] = line->c;
		while (line->line[j])
			str[i++] = line->line[j++];
		str[i] = '\0';
		free(line->line);
		line->line = str;
	}
	return ;
}

void		strcat_inline(char ret, t_line *line)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (ret > 31 && ret < 127)
	{
		line->c = ret;
		ft_strlinecat(line);
		line->count++;
		if (line->count + 4 == ws.ws_col)
			line->iline++;
		ft_putchar_fd(ret, 0);
	}
}

int			sigline(int i, int mode)
{
	static int	tmp;

	if (mode == 1)
		tmp = i;
	return (tmp);
}

int			has_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= 33 && line[i] <= 126)
			return (1);
		i++;
	}
	return (0);
}
