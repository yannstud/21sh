/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 01:14:17 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:26 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		moove_curs_right(t_elem **list)
{
	t_elem *tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->next && tmp->cursor == 1)
		{
			tmp->cursor = 0;
			tmp = tmp->next;
			tmp->cursor = 1;
			return ;
		}
		else if (!tmp->next && tmp->cursor == 1)
		{
			tmp->cursor = 0;
			tmp = *list;
			tmp->cursor = 1;
			return ;
		}
		else
			tmp = tmp->next;
	}
}

void		moove_curs_left(t_elem **list)
{
	t_elem *tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->prev && tmp->cursor == 1)
		{
			tmp->cursor = 0;
			tmp = tmp->prev;
			tmp->cursor = 1;
			return ;
		}
		else if (!tmp->prev && tmp->cursor == 1)
		{
			tmp->cursor = 0;
			while (tmp->next)
				tmp = tmp->next;
			tmp->cursor = 1;
			return ;
		}
		else
			tmp = tmp->next;
	}
}

void		choose(t_elem **list)
{
	t_elem	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->cursor == 1)
		{
			tmp->select = 1;
			return ;
		}
		tmp = tmp->next;
	}
}
