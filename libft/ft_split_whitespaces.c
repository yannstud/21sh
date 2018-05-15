/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:16:28 by ysalaun           #+#    #+#             */
/*   Updated: 2018/01/29 18:47:27 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_count_words(char const *str)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
			count++;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
			i++;
	}
	return (count);
}

static int		get_word_len(char const *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char			**ft_split_whitespaces(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	**str2;

	if (!s || !(str2 = (char **)ft_memalloc(sizeof(*str2) *
		(ft_count_words(s) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_count_words(s))
	{
		k = 0;
		if (!(str2[i] = ft_strnew(get_word_len(&s[j]) + 1)))
			str2[i] = NULL;
		while (s[j] == ' ' || s[j] == '\t')
			j++;
		while (s[j] != ' ' && s[j] != '\t' && s[j])
			str2[i][k++] = s[j++];
		str2[i][k] = '\0';
	}
	str2[i] = 0;
	return (str2);
}
