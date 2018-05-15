/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:12:43 by ysalaun           #+#    #+#             */
/*   Updated: 2017/11/11 20:16:36 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_list;
	t_list *tmp;

	if (lst == NULL)
		return (NULL);
	new_list = f(lst);
	tmp = new_list;
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (!(new_list->next = f(lst)))
		{
			new_list->next = NULL;
			return (NULL);
		}
		new_list = new_list->next;
	}
	return (tmp);
}
