/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stractions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:07:10 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:38 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

char			*ft_strindexcat(char *dest, char *src, size_t index)
{
	int		i;
	int		j;
	char	*tmp;

	if (index == ft_strlen(dest))
		return (ft_strcat(dest, src));
	i = index;
	while (dest[i])
		i++;
	if (!(tmp = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = index;
	j = 0;
	while (dest[i])
		tmp[j++] = dest[i++];
	i = index;
	j = 0;
	while (src[j])
		dest[i++] = src[j++];
	j = 0;
	while (tmp[j])
		dest[i++] = tmp[j++];
	free(tmp);
	return (dest);
}

void			left(size_t i)
{
	size_t k;

	k = 0;
	while (k < i)
	{
		ft_putstr_fd(tgetstr("le", NULL), 0);
		ft_putstr_fd(tgetstr("dc", NULL), 0);
		k++;
	}
	ft_putstr_fd(tgetstr("cd", NULL), 0);
}

void			left2(t_line *line)
{
	size_t i;

	i = ft_strlen(line->line) + 1;
	while (--i > line->count)
		ft_putstr_fd(tgetstr("le", NULL), 0);
}

struct termios	sigleton(struct termios term)
{
	static struct termios term2;

	if (term.c_cflag)
		term2 = term;
	return (term2);
}
