/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 03:12:47 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/25 18:03:21 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

pid_t		ft_pid(pid_t pid, int i)
{
	static pid_t	tmp;

	if (i == 1)
		tmp = pid;
	else if (i == 2)
		tmp = 0;
	return (tmp);
}

void		sig_int(void)
{
	pid_t pid;

	pid = 0;
	pid = ft_pid(0, 0);
	if (pid >= 1)
		kill(pid, 9);
	print_prompt(1);
	sigline(1, 1);
}

void		sig_handler(int sig)
{
	char str[3];

	if (sig == SIGWINCH)
	{
		read(0, str, 3);
		ft_putstr_fd(tgetstr("le", NULL), 1);
		ft_putstr_fd(tgetstr("nd", NULL), 1);
	}
	else if (sig == SIGINT)
		sig_int();
	else if (sig == SIGQUIT ||
		sig == SIGKILL || sig == SIGTERM)
		exit_term(0);
	else
		return ;
}

void		sig_c(t_line *line, t_cmd *cmd)
{
	if (sigline(0, 0) == 1)
	{
		ft_bzero(line->line, ft_strlen(line->line));
		line->count = 0;
		reset_cmd(&cmd);
	}
	sigline(0, 1);
}

void		ft_signal(void)
{
	int		i;

	i = 0;
	while (i < 33)
	{
		signal(i, sig_handler);
		i++;
	}
	signal(SIGSEGV, NULL);
	signal(SIGTSTP, SIG_IGN);
}
