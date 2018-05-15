/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 06:40:26 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/26 11:31:27 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		calc_size_needed(t_elem **alst)
{
	t_elem			*tmp;
	int				count;
	int				max_word;
	int				count_lines;
	struct winsize	ws;

	tmp = *alst;
	count = -1;
	count_lines = 0;
	ioctl(0, TIOCGWINSZ, &ws);
	max_word = calc_term_larg(alst);
	while (tmp)
	{
		if (++count == max_word)
		{
			ft_putchar_fd('\n', 0);
			if (++count_lines >= ws.ws_row)
				return (print_too_small());
			count = 0;
		}
		print_my_names(tmp, alst);
		tmp = tmp->next;
	}
	return_back(count_lines, ws.ws_col);
}

void		termcaps_begin_select(t_elem **alst)
{
	ft_putstr_fd(tgetstr("do", NULL), 0);
	calc_size_needed(alst);
	ft_putstr_fd(tgetstr("sc", NULL), 0);
	ft_putstr_fd(tgetstr("vi", NULL), 0);
}

t_elem		*parsing_error_select(t_line *line, char **env)
{
	char		*str;
	t_elem		*alst;

	if (line && line->count != ft_strlen(line->line))
	{
		ft_putstr_fd(tgetstr("ve", NULL), 0);
		return (NULL);
	}
	str = ft_strdup(line->line);
	alst = parsing_path(env, str, line);
	free(str);
	if (alst && !alst->next)
	{
		ft_putstr_fd(tgetstr("ve", NULL), 0);
		quit_select(line, &alst, 1);
		return (NULL);
	}
	termcaps_begin_select(&alst);
	return (alst);
}

void		autocompletion(t_line *line, char **env)
{
	char		ret[3];
	t_elem		*alst;

	if ((alst = parsing_error_select(line, env)) == NULL)
		return ;
	while (42)
	{
		print_list(&alst);
		ft_bzero(ret, 3);
		read(0, ret, 3);
		if (ret[0] == 9 && ret[1] == 0 && ret[2] == 0)
			moove_curs_right(&alst);
		else if (ret[0] == 27)
			whitch_select_arrow(ret, &alst);
		else if (ret[0] == 10 && ret[1] == 0 && ret[2] == 0)
		{
			termcaps_end_select(0);
			choose(&alst);
			return_elem(&alst, line);
			return (ft_putstr_fd(tgetstr("ve", NULL), 0));
		}
		else if (ret[0] != 10 || ret[0] != 9 || ret[0] != 27)
			return (quit_select(line, &alst, 1));
		termcaps_end_select(1);
	}
}
