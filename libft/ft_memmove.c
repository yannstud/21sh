/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:12:43 by ysalaun           #+#    #+#             */
/*   Updated: 2018/01/16 11:57:08 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*byte_dest;
	char			*byte_src;
	size_t			count;

	count = 0;
	byte_dest = (char*)dest;
	byte_src = (char*)src;
	while (dest >= src && n--)
		byte_dest[n] = byte_src[n];
	while (dest < src && count < n)
	{
		byte_dest[count] = byte_src[count];
		count++;
	}
	return (dest);
}
