/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:12:43 by ysalaun           #+#    #+#             */
/*   Updated: 2017/11/12 19:04:49 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	int		count;

	i = 0;
	count = 0;
	if (to_find[0] == '\0')
		return ((char *)&str[0]);
	while (str[i] && i < len)
	{
		j = i;
		count = 0;
		while (str[j] == to_find[count] && j < len)
		{
			j++;
			count++;
			if (to_find[count] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (0);
}
