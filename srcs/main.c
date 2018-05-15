/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 06:38:48 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/26 13:36:30 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		launch_exec(t_history *list, t_cmd **cmd)
{
	restore_term_ori();
	(*cmd)->ast = create_ast((*cmd)->head);
	if ((*cmd)->debug)
		print_tree_prefix((*cmd)->ast);
	exec_recursive((*cmd)->ast, (*cmd)->enva, 1, *cmd);
	clean_tree((*cmd)->ast);
	create_history((*cmd)->command, list);
	set_cmd(NULL, cmd);
	restore_fds();
	re_init_term();
}

void		parsing_ok(t_history *list, t_cmd **cmd)
{
	if (gestion_quotes2((*cmd)->command))
	{
		if ((!(*cmd)->heredoc_mode) && parse_heredoc(cmd))
		{
			(*cmd)->heredoc_mode = 1;
			(*cmd)->give_me_more = 1;
		}
		else if (last_is_oper((*cmd)->head, (*cmd)->command))
			(*cmd)->give_me_more = 2;
		else if ((*cmd)->heredoc_mode == 2)
			launch_exec(list, cmd);
	}
	else
		(*cmd)->give_me_more = 1;
}

void		end_enter(t_cmd **cmd)
{
	if (singlexex(2) == 0)
	{
		if (!((*cmd)->give_me_more))
			print_prompt(0);
		else
			ft_putstr_fd("> ", 0);
	}
	singlexex(0);
}

void		enter(t_line *line, t_history *list, t_cmd **cmd)
{
	ft_putstr_fd("\n", 0);
	if (has_line(line->line) || (*cmd)->heredoc_mode == 2)
	{
		set_cmd(line->line, cmd);
		get_token(&(*cmd)->head, (*cmd)->command);
		if ((*cmd)->debug == 1)
			print_tokens((*cmd)->head);
		if (parsing((*cmd)->head))
			parsing_ok(list, cmd);
		else
		{
			free_token((*cmd)->head);
			create_history((*cmd)->command, list);
			set_cmd(NULL, cmd);
		}
		free_token((*cmd)->head);
	}
	(*cmd)->head = NULL;
	ft_bzero(line->line, ft_strlen(line->line));
	line->count = 0;
	line->iline = 0;
	end_enter(cmd);
}

int			main(void)
{
	char			ret[0];
	struct winsize	ws;
	t_history		*list;
	t_line			line;
	t_cmd			*cmd;

	if (!(cmd = init_cmd()))
		return (0);
	if ((list = init_history()) == NULL)
		exit_term(0);
	init(&line);
	while (42)
	{
		ioctl(0, TIOCGWINSZ, &ws);
		line.icol = ws.ws_col;
		ft_bzero(ret, 1);
		read(0, ret, 1);
		sig_c(&line, cmd);
		line.ret = ret[0];
		all_ifs(&line, ret, &cmd, list);
	}
	return (0);
}
