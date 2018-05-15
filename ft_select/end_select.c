/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 02:41:57 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:24 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void			ft_freet_elem(t_elem **list)
{
	t_elem *elem;

	elem = *list;
	while (elem->next)
	{
		free(elem->name);
		elem = elem->next;
		free(elem->prev);
	}
	free(elem->name);
	free(elem);
}

char			*set_name(t_line *line, t_elem *tmp)
{
	char		*str;
	int			i;
	int			j;

	str = ft_strnew(5000);
	i = -1;
	while (line->line[++i])
		str[i] = line->line[i];
	while (--i > 0 && line->line[i] != ' ')
		str[i] = ' ';
	if (i > 0)
		str[i++] = ' ';
	j = -1;
	while (tmp->name[++j])
		str[i++] = tmp->name[j];
	return (str);
}

void			return_elem(t_elem **list, t_line *line)
{
	t_elem		*tmp;
	char		*str;

	tmp = *list;
	while (tmp)
	{
		if (tmp->select == 1)
		{
			str = set_name(line, tmp);
			ft_putstr_fd(tgetstr("up", NULL), 0);
			ft_putstr_fd(tgetstr("cd", NULL), 0);
			line->count = ft_strlen(str);
			free(line->line);
			line->line = ft_strdup(str);
			ft_freet_elem(list);
			free(str);
			print_prompt(0);
			ft_putstr_fd(line->line, 0);
			return ;
		}
		tmp = tmp->next;
	}
}

void			quit_select(t_line *line, t_elem **alst, int i)
{
	ft_freet_elem(alst);
	if (i == 1)
	{
		print_prompt(1);
		ft_putstr_fd(line->line, 0);
	}
	ft_putstr_fd(tgetstr("ve", NULL), 0);
}

void			termcaps_end_select(int i)
{
	ft_putstr_fd(tgetstr("rc", NULL), 0);
	if (i == 1)
		ft_putstr_fd(tgetstr("sc", NULL), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
}
