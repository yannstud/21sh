/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 01:19:59 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:27 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void			print_list(t_elem **alst)
{
	t_elem			*tmp;
	int				count;
	int				max_word;
	int				count_lines;
	struct winsize	ws;

	tmp = *alst;
	count = -1;
	count_lines = 0;
	ioctl(0, TIOCGWINSZ, &ws);
	max_word = calc_term_larg(alst);
	while (tmp)
	{
		if (max_size_words(alst) + 5 > ws.ws_col)
			return (print_too_small());
		if (++count == max_word)
		{
			ft_putchar_fd('\n', 0);
			if (++count_lines >= ws.ws_row)
				return (print_too_small());
			count = 0;
		}
		print_my_names(tmp, alst);
		tmp = tmp->next;
	}
}

void			print_my_names(t_elem *tmp, t_elem **alst)
{
	if (tmp->cursor == 1)
		ft_putstr_fd("\033[31m", 0);
	if (ft_strlen(tmp->name) % 2 == 0)
		ft_putchar_fd(' ', 0);
	resize_names(alst, tmp->name, 1, tmp->cursor);
	ft_putstr_fd(tmp->name, 0);
	resize_names(alst, tmp->name, 0, 0);
	ft_putstr_fd(NORMAL, 0);
}

void			print_too_small(void)
{
	ft_putstr_fd(tgetstr("cl", NULL), 1);
	ft_putstr_fd("i am too small", 0);
}

t_line			*singleline(t_line *line)
{
	static t_line *line2;

	if (line->line)
		line2 = line;
	return (line2);
}
