/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:12:43 by ysalaun           #+#    #+#             */
/*   Updated: 2017/11/16 00:29:00 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t siz)
{
	size_t		i;
	size_t		j;
	char		*str;

	str = (char*)src;
	i = 0;
	if (siz == 0)
		return (ft_strlen(src));
	while (dst[i] && i < siz)
		i++;
	j = i;
	while (str[i - j] && i < siz - 1)
	{
		dst[i] = str[i - j];
		i++;
	}
	if (j < siz)
		dst[i] = '\0';
	return (j + ft_strlen(str));
}
