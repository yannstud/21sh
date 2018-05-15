/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 18:22:23 by ysalaun           #+#    #+#             */
/*   Updated: 2017/11/12 20:27:02 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(int nb, unsigned int base)
{
	unsigned int	i;
	unsigned int	k;
	int				tab[base];

	k = -1;
	while (++k < base)
	{
		if (k < 10)
			tab[k] = k + '0';
		else
			tab[k] = 'A' + k - 10;
	}
	i = nb;
	if (nb < 0)
	{
		i = -nb;
		ft_putchar('-');
	}
	if (i >= base)
	{
		ft_putnbr_base(i / base, base);
		ft_putnbr_base(i % base, base);
	}
	else
		ft_putchar(tab[i]);
}
