/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdouble_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:36:06 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/06 13:46:29 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		count_params(char const *str, char c, char b)
{
	int i;
	int word;

	word = 0;
	i = 0;
	while ((str[i] == c || str[i] == b) && str[i] != '\0')
		i++;
	while (str[i])
	{
		word++;
		while ((str[i] != c || str[i] != b) && str[i])
		{
			i++;
		}
		while ((str[i] == c || str[i] == b) && str[i])
			i++;
	}
	return (word);
}

static int		count_caracs(char const *str, int *pos, char c, char b)
{
	int letter;

	letter = 0;
	while (str[*pos] == c || str[*pos] == b)
		(*pos)++;
	while ((str[*pos] != c || str[*pos] != b) && str[*pos])
	{
		letter++;
		(*pos)++;
	}
	return (letter - 1);
}

static char		*write_my_tab(char const *str, int *pos, char c, char b)
{
	int		k;
	char	*tab;
	int		i;
	int		count;

	tab = NULL;
	while (str[*pos] == c || str[*pos] == b)
		(*pos)++;
	i = *pos;
	count = count_caracs(str, pos, c, b);
	tab = (char *)ft_memalloc(sizeof(char) * count + 1);
	k = 0;
	while (k <= count)
	{
		tab[k] = str[i];
		k++;
		i++;
	}
	tab[k] = '\0';
	return (tab);
}

char			**ft_strdouble_split(char const *s, char c, char b)
{
	int		k;
	char	**tab;
	int		pos;
	int		count_par;

	if (s == NULL)
		return (0);
	count_par = count_params(s, c, b);
	pos = 0;
	k = 0;
	if (s == 0)
		return (0);
	tab = (char**)ft_memalloc(sizeof(char*) * count_par + 1);
	if (tab == NULL)
		return (0);
	while (k < count_par)
	{
		tab[k] = write_my_tab(s, &pos, c, b);
		k++;
	}
	tab[k] = NULL;
	return (tab);
}
