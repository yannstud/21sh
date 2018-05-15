/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 23:27:35 by ysalaun           #+#    #+#             */
/*   Updated: 2018/02/01 02:42:55 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		free_double_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_memdel((void **)(&tab[i]));
		i++;
	}
	ft_memdel((void **)(&tab));
}
