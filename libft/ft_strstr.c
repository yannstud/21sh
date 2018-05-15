/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:12:43 by ysalaun           #+#    #+#             */
/*   Updated: 2017/11/12 19:04:58 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	if (to_find[0] == '\0')
		return ((char *)&str[0]);
	while (str[i])
	{
		j = i;
		count = 0;
		while (str[j] == to_find[count])
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
