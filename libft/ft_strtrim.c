/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:12:43 by ysalaun           #+#    #+#             */
/*   Updated: 2017/11/11 00:35:53 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_par(const char *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	while (s[i] != '\0')
	{
		i++;
		j++;
	}
	i--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i--;
		j--;
	}
	return (j);
}

static int		count_before(const char *s)
{
	int i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = NULL;
	if (s == NULL)
		return (0);
	if (count_par(s) == 0 || count_before(s) == (int)ft_strlen(s))
		return (ft_strnew(1));
	if ((str = (char *)ft_memalloc(sizeof(char) * count_par(s) + 1)) == 0)
		return (0);
	i = count_before(s);
	while (j < count_par(s))
	{
		str[j++] = s[i++];
		str[j] = '\0';
	}
	str[j] = '\0';
	return (str);
}
