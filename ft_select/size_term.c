/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 01:34:21 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:28 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int				max_size_words(t_elem **list)
{
	t_elem		*tmp;
	size_t		count;

	count = 0;
	tmp = *list;
	while (tmp)
	{
		if (count < ft_strlen(tmp->name))
			count = ft_strlen(tmp->name);
		tmp = tmp->next;
	}
	return (count);
}

void			resize_names(t_elem **list, char *name, size_t t, int cursor)
{
	size_t i;
	size_t count;

	count = max_size_words(list);
	i = 0;
	if (cursor == 1)
	{
		ft_putchar_fd('>', 0);
		t--;
	}
	while (i < (count / 2) - (ft_strlen(name) / 2) + t)
	{
		ft_putchar_fd(' ', 0);
		i++;
	}
}

int				calc_term_larg(t_elem **list)
{
	int				len_max;
	struct winsize	ws;
	int				word_max;

	ioctl(0, TIOCGWINSZ, &ws);
	len_max = max_size_words(list) + 5;
	word_max = 0;
	word_max = ws.ws_col / len_max;
	return (word_max);
}
