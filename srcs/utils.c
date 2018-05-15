/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:37:45 by amottier          #+#    #+#             */
/*   Updated: 2018/04/26 14:51:18 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		init(t_line *line)
{
	init_term();
	ft_signal();
	line->iline = 0;
	line->line = ft_strnew(1);
	ft_bzero(line->line, 1);
	line->count = 0;
	print_prompt(0);
}

void		all_ifs(t_line *line, char *ret, t_cmd **cmd, t_history *list)
{
	extern char		**environ;

	if (ret[0] == 27 || ret[0] == 11 || ret[0] == 16 || ret[0] == 127 ||
		ret[0] == 9 || ret[0] == 12 || ret[0] == 4)
		witch_arrow(list, line, environ, cmd);
	else if (ret[0] == 10)
		enter(line, list, cmd);
	else if (line->line && line->count == ft_strlen(line->line))
		strcat_inline(ret[0], line);
	else if (ret[0] > 31 && ret[0] < 127)
		insert_inline(line, ret[0]);
}

char		*get_home(char *pwd)
{
	size_t		i;
	int			j;
	char		*new_pwd;

	i = 0;
	while (pwd[i])
		i++;
	new_pwd = ft_strnew(i);
	i = 5;
	j = 0;
	while (pwd[i])
	{
		new_pwd[j] = pwd[i];
		i++;
		j++;
	}
	free(pwd);
	return (new_pwd);
}

int			gestion_ctrl_d(char *buffer, t_cmd **cmd, t_line *line,
				t_history *list)
{
	if (buffer[0] == 4 && line->line[0])
		return (1);
	else if (buffer[0] == 4 && !line->line[0])
	{
		if ((*cmd)->give_me_more == 1 && (*cmd)->heredoc_mode != 1)
			return (1);
		if ((*cmd)->heredoc_mode == 1)
		{
			(*cmd)->heredoc_mode = 2;
			(*cmd)->give_me_more = 0;
			enter(line, list, cmd);
			return (1);
		}
		exit_term(0);
	}
	return (0);
}
