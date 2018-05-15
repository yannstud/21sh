/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:54:29 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:25 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		whitch_select_arrow(char *buff, t_elem **list)
{
	if (buff[2] == 'D')
		moove_curs_left(list);
	else if (buff[2] == 'C' || (buff[0] == 9 && buff[1] == 0 && buff[2] == 0))
		moove_curs_right(list);
}

t_elem		*init_select_list(void)
{
	t_elem	*new;

	if ((new = malloc(sizeof(t_elem))) == NULL)
		return (NULL);
	new->name = ft_strdup(" ");
	new->select = 0;
	new->cursor = 1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		add_front_select_list(t_elem **alst, t_elem *new, char *name)
{
	t_elem	*tmp;

	tmp = *alst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new = malloc(sizeof(t_elem));
	tmp->next = new;
	new->name = ft_strdup(name);
	new->next = NULL;
	new->select = 0;
	new->cursor = 0;
	new->prev = tmp;
}
