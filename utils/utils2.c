/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 11:33:44 by amottier          #+#    #+#             */
/*   Updated: 2018/04/27 12:17:37 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int		open_file(char *filename, int append, int read)
{
	int fd;

	if (read)
		fd = open(filename, O_RDONLY);
	else if (append)
		fd = open(filename, O_WRONLY | O_APPEND
			| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(filename, O_WRONLY | O_TRUNC
			| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		if (access(filename, F_OK) == -1)
			err_no_file(filename);
		else if ((!read && access(filename, W_OK) != 0)
			|| (read && access(filename, R_OK) != 0))
			err_no_file_perm(filename);
	}
	return (fd);
}
