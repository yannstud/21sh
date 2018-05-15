/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:20:40 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:59:16 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int			ft_echo(t_env **env, char **tabz)
{
	int i;
	int	op_n;

	i = 1;
	op_n = 0;
	(void)env;
	if (tabz[1] && !(ft_strcmp(tabz[1], "-n")))
	{
		i++;
		op_n = 1;
	}
	while (tabz[i])
	{
		if (i > (1 + op_n))
			ft_putchar(' ');
		ft_putstr(tabz[i]);
		i++;
	}
	if (!(op_n))
		ft_putchar('\n');
	return (0);
}
