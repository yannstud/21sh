/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 01:58:49 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:58 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		clear_histo(t_line *line)
{
	while (line->count > 0)
		curs_left(line);
	ft_putstr_fd(tgetstr("cd", NULL), 1);
}

char		*get_last_command(t_history **alst)
{
	t_history	*tmp;
	char		*line;

	line = NULL;
	tmp = *alst;
	while (tmp->cursor != 1)
		tmp = tmp->next;
	if (tmp->command[0] && ft_strlen(tmp->command) > 0)
	{
		line = ft_strdup(tmp->command);
		ft_putstr_fd(tmp->command, 0);
	}
	if (tmp->prev)
	{
		tmp->cursor = 0;
		tmp = tmp->prev;
		tmp->cursor = 1;
	}
	return (line);
}

char		*get_next_command(t_history **alst)
{
	t_history	*tmp;
	char		*line;

	line = NULL;
	tmp = *alst;
	while (tmp->cursor != 1)
		tmp = tmp->next;
	if (tmp->next && tmp->next->next)
	{
		tmp->cursor = 0;
		tmp = tmp->next;
		tmp->cursor = 1;
		line = ft_strdup(tmp->next->command);
		ft_putstr_fd(tmp->next->command, 0);
	}
	return (line);
}

int			control_l(t_line *line)
{
	ft_putstr_fd(tgetstr("cl", NULL), 1);
	print_prompt(0);
	ft_putstr_fd(line->line, 0);
	return (1);
}
