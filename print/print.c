/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 14:14:10 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:58:48 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int			print_env_list(t_env *env)
{
	t_env		*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr(tmp->name);
		ft_putchar('=');
		ft_putendl(tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

void		print_prompt(int i)
{
	ft_putstr_fd("\033[31m", 0);
	if (i == 1)
		ft_putchar('\n');
	ft_putstr_fd("➜  ", 0);
	ft_putstr_fd("\033[0m", 0);
}
