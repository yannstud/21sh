/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:20:04 by ysalaun           #+#    #+#             */
/*   Updated: 2018/01/25 20:45:08 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		count_params(char const *str, char c)
{
	int i;
	int word;

	word = 0;
	i = 0;
	while (str[i] == c && str[i] != '\0')
		i++;
	while (str[i])
	{
		word++;
		while (str[i] != c && str[i])
		{
			i++;
		}
		while (str[i] == c && str[i])
			i++;
	}
	return (word);
}

static int		count_caracs(char const *str, int *pos, char c)
{
	int letter;

	letter = 0;
	while (str[*pos] == c)
		(*pos)++;
	while (str[*pos] != c && str[*pos])
	{
		letter++;
		(*pos)++;
	}
	return (letter);
}

static char		*write_my_tab(char const *str, int *pos, char c)
{
	int		k;
	char	*tab;
	int		i;
	int		count;

	tab = NULL;
	while (str[*pos] == c)
		(*pos)++;
	i = *pos;
	count = count_caracs(str, pos, c);
	tab = (char *)ft_memalloc(sizeof(char) * (count + 1));
	k = 0;
	while (k < count)
	{
		tab[k] = str[i];
		k++;
		i++;
	}
	tab[k] = '\0';
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	int		k;
	char	**tab;
	int		pos;
	int		count_par;

	if (s == NULL)
		return (0);
	count_par = count_params(s, c);
	pos = 0;
	k = 0;
	if (s == 0)
		return (0);
	tab = (char**)ft_memalloc(sizeof(char*) * (count_par + 1));
	if (tab == NULL)
		return (0);
	while (k < count_par)
	{
		tab[k] = write_my_tab(s, &pos, c);
		k++;
	}
	tab[k] = NULL;
	return (tab);
}
