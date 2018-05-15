/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 14:08:25 by amottier          #+#    #+#             */
/*   Updated: 2018/04/27 11:45:32 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		parsing_error(char *str)
{
	ft_putstr_fd("21sh: parse error near `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
}

int			err_no_file_perm(char *msg)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(": Permission denied", 2);
	return (1);
}
