/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:03:56 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:59:03 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void			restore_fds(void)
{
	t_fds		*fds;

	fds = get_terminal();
	if (fds->fd_stdin != -1)
		dup2(fds->fd_stdin, STDIN_FILENO);
	else
		close(STDIN_FILENO);
	if (fds->fd_stderr != -1)
		dup2(fds->fd_stderr, STDERR_FILENO);
	else
		close(STDERR_FILENO);
	if (fds->fd_stdout != -1)
		dup2(fds->fd_stdout, STDOUT_FILENO);
	else
		close(STDOUT_FILENO);
}

static t_fds	*init_fds(void)
{
	t_fds		*fds;

	if (!(fds = malloc(sizeof(t_fds))))
		return (NULL);
	fds->fd_stdin = 100;
	fds->fd_stdout = 101;
	fds->fd_stderr = 102;
	if (dup2(STDIN_FILENO, fds->fd_stdin) == -1)
	{
		close(fds->fd_stdin);
		fds->fd_stdin = -1;
	}
	if (dup2(STDERR_FILENO, fds->fd_stderr) == -1)
	{
		close(fds->fd_stderr);
		fds->fd_stderr = -1;
	}
	if (dup2(STDOUT_FILENO, fds->fd_stdout) == -1)
	{
		close(fds->fd_stdout);
		fds->fd_stdout = -1;
	}
	return (fds);
}

t_fds			*get_terminal(void)
{
	static t_fds *fds = NULL;

	if (fds == NULL)
		fds = init_fds();
	return (fds);
}
