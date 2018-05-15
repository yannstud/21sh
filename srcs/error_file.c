/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:49:55 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:52 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		print_error(char *new_path)
{
	if (ft_strcmp(new_path, "-i") != 0)
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(new_path, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void		print_error_file(char *command)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void		free_args(char **str, char **str2, char **str3, char *str4)
{
	if (str)
		free_double_tab(str);
	if (str2)
		free_double_tab(str2);
	if (str3)
		free_double_tab(str3);
	if (str4)
		ft_memdel((void**)&str4);
}
