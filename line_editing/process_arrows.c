/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arrows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:55:27 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/26 13:39:01 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int			instant_arrow(char *buffer, t_line *line, char **env)
{
	if (buffer[0] == 127)
		return (del_left(line));
	else if (buffer[0] == 11)
		return (control_k(line));
	else if (buffer[0] == 16)
		return (control_p(line));
	else if (buffer[0] == 9 && line->line[0])
	{
		autocompletion(line, env);
		return (1);
	}
	else if (buffer[0] == 12)
		return (control_l(line));
	else
		return (0);
}

void		last_command(t_history *list, t_line *line, char *ret)
{
	if (ret[1] == 'A')
	{
		clear_histo(line);
		free(line->line);
		if (!(line->line = get_last_command(&list)))
		{
			line->line = ft_strnew(1);
			line->count = 0;
			return ;
		}
		line->count = ft_strlen(line->line);
		return ;
	}
}

void		next_command(t_history *list, t_line *line, char *ret)
{
	if (ret[1] == 'B')
	{
		free(line->line);
		clear_histo(line);
		if (!(line->line = get_next_command(&list)))
		{
			line->line = ft_strnew(1);
			line->count = 0;
			return ;
		}
		line->count = ft_strlen(line->line);
		return ;
	}
}

void		process_dcab(char *ret, t_line *line, t_history *list)
{
	if (ret[1] == 'D')
		return (curs_left(line));
	else if (ret[1] == 'C')
		return (curs_right(line));
	else if (ret[1] == 'A')
		return (last_command(list, line, ret));
	else if (ret[1] == 'B')
		return (next_command(list, line, ret));
}

void		witch_arrow(t_history *list, t_line *line, char **env, t_cmd **cmd)
{
	char ret[2];

	if (instant_arrow(&line->ret, line, env) == 1)
		return ;
	if (gestion_ctrl_d(&line->ret, cmd, line, list) == 1)
		return ;
	ft_bzero(ret, 2);
	read(0, ret, 2);
	if (line->ret == 27 && ret[1] == 72)
		return (go_home(line));
	else if (line->ret == 27 && ret[1] == 70)
		return (go_end(line));
	else if (line->ret == 27 && ret[0] == 27 && ret[1] == 91)
		return (opt_left_right(line));
	else if (line->ret == 27 && ret[0] == 102 && ret[1] == 0)
		return (opt_right(line));
	else if (line->ret == 27 && ret[0] == 98 && ret[1] == 0)
		return (opt_left(line));
	else if (line->ret == 27 && ret[0] == 91 && ret[1] == 51)
		return (right_del(line));
	else if (ret[1] == 'D' || ret[1] == 'C' || ret[1] == 'A' || ret[1] == 'B')
		return (process_dcab(ret, line, list));
	return ;
}
