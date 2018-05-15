/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcapsactions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:33:55 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/26 11:28:40 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void			init_term(void)
{
	char			*term_name;
	struct termios	term;
	struct termios	term_ori;

	if ((term_name = getenv("TERM")) == NULL)
	{
		ft_putstr("No available environemment\n");
		exit(0);
	}
	if (tgetent(NULL, term_name) == ERR)
		exit(0);
	if (tcgetattr(0, &term) == -1)
		exit(0);
	term_ori = term;
	sigleton(term_ori);
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
}

void			restore_term_ori(void)
{
	struct termios term;

	ft_bzero(&term, sizeof(struct termios));
	term = sigleton(term);
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &term);
}

void			re_init_term(void)
{
	struct termios	term;
	struct termios	term_ori;

	if (tcgetattr(0, &term) == -1)
		exit(0);
	term_ori = term;
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
}

void			exit_term(int i)
{
	struct termios term;

	ft_bzero(&term, sizeof(struct termios));
	term = sigleton(term);
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &term);
	exit(i);
}
