/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 23:20:50 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:13 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		print_line(char *str)
{
	size_t i;

	i = ft_strlen(str);
	while (i + 4 > 0)
	{
		ft_putstr_fd(tgetstr("le", NULL), 1);
		i--;
	}
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	print_prompt(0);
	ft_putstr_fd(str, 0);
}

int			control_k(t_line *line)
{
	size_t i;
	size_t j;

	i = line->count;
	j = 0;
	while (line->line[i])
	{
		i++;
		j++;
	}
	if (line->selected && ft_isprint(line->selected[0]) == 1)
		free(line->selected);
	line->selected = ft_strnew(j + 1);
	i = line->count;
	j = 0;
	while (line->line[i])
	{
		line->selected[j] = line->line[i];
		line->line[i++] = '\0';
		j++;
	}
	line->selected[j] = '\0';
	line->count = ft_strlen(line->line);
	print_line(line->line);
	return (1);
}

char		*make_str(char *str, char *line, char *selected, size_t count)
{
	size_t	i;
	size_t	j;
	size_t	t;
	char	*tmp;

	i = -1;
	while (++i < count)
		str[i] = line[i];
	t = i;
	tmp = ft_strnew(ft_strlen(line));
	j = 0;
	while (line[i])
		tmp[j++] = line[i++];
	j = 0;
	while (selected[j])
		str[t++] = selected[j++];
	j = 0;
	while (tmp[j])
		str[t++] = tmp[j++];
	str[t] = '\0';
	free(tmp);
	return (str);
}

int			control_p(t_line *line)
{
	char			*str;
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (line->selected && ft_isprint(line->selected[0]))
	{
		str = ft_strnew(ft_strlen(line->line) + ft_strlen(line->selected) + 1);
		str = make_str(str, line->line, line->selected, line->count);
		free(line->line);
		line->line = ft_strdup(str);
		free(str);
		line->count = ft_strlen(line->line);
		print_line(line->line);
	}
	return (1);
}
