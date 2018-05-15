/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:12:43 by ysalaun           #+#    #+#             */
/*   Updated: 2017/11/10 18:32:47 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		calc_size(int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int		div;
	char	*str;
	int		i;

	i = 0;
	div = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if ((str = malloc(sizeof(char) * (calc_size(n) + 2))) == 0)
		return (0);
	if (n < 0)
	{
		str[i++] = '-';
		n = -n;
	}
	while (n / div >= 10)
		div *= 10;
	while (div > 0)
	{
		str[i] = n / div % 10 + '0';
		div /= 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}
