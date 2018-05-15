/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:12:43 by ysalaun           #+#    #+#             */
/*   Updated: 2017/11/08 21:20:47 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*rendu;
	int		i;

	i = 0;
	if ((rendu = (char *)ft_memalloc(sizeof(char) * ft_strlen(str) + 1)) == 0)
		return (0);
	while (str[i])
	{
		rendu[i] = str[i];
		i++;
	}
	rendu[i] = '\0';
	return (rendu);
}
