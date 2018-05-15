/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dellistselect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 01:08:05 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:59:06 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		del_without_next(t_elem *list)
{
	list->prev->next = NULL;
	list->prev->cursor = 1;
	freenode(list);
}

void		del_without_prev(t_elem *list)
{
	list->next->prev = NULL;
	list->next->cursor = 1;
	freenode(list);
}

void		del_with_all(t_elem *list)
{
	list->next->cursor = 1;
	list->prev->next = list->next;
	list->next->prev = list->prev;
	freenode(list);
}

void		freenode(t_elem *node)
{
	free(node->name);
	free(node);
}

void		return_back(int count_lines, int ws_col)
{
	int		i;

	while (count_lines--)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	i = 0;
	while (i < ws_col)
	{
		ft_putstr_fd(tgetstr("le", NULL), 0);
		i++;
	}
}
