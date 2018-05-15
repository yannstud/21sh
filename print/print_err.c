/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 14:08:25 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:58:49 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		print_err(char *name, int type)
{
	if (type == 1)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void		print_err_cd(int stat_res, char *path, struct stat path_stat)
{
	if (stat_res == -1)
		ft_putstr_fd("cd: no such file or directory: ", 2);
	else if (S_ISREG(path_stat.st_mode))
		ft_putstr_fd("cd: not a directory: ", 2);
	else if (!(path_stat.st_mode & S_IRUSR))
		ft_putstr_fd("cd: permission denied: ", 2);
	ft_putendl_fd(path, 2);
}

int			err_no_file(char *msg)
{
	ft_putstr_fd("21sh: no such file or directory: ", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

int			err_no_fd(int fd_nbr)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putnbr_fd(fd_nbr, 2);
	ft_putendl_fd(": bad file descriptor", 2);
	return (1);
}

void		err_no_cmd(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Command not found", 2);
}
