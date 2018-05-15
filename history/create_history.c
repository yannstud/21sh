/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 23:33:30 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/26 11:26:33 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		create_history(char *command, t_history *list)
{
	int			fd;

	if (command && ft_strlen(command) < 5000)
	{
		if ((fd = open("/tmp/.history", O_RDWR | O_APPEND | O_CREAT, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			exit_term(0);
		ft_putendl_fd(command, fd);
		add_front_history(&list, command);
		close(fd);
	}
}

t_history	*init_list(char *name)
{
	t_history	*new;

	new = ft_memalloc(sizeof(t_history));
	new->command = ft_strdup(name);
	new->cursor = 1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int			check_name(char *str)
{
	int i;

	i = 0;
	if (ft_strlen(str) > 5000)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n' || ft_isprint(str[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

void		add_front_history(t_history **alst, char *name)
{
	t_history	*tmp;
	t_history	*new;

	tmp = *alst;
	if (name)
	{
		while (tmp->next)
		{
			tmp->cursor = 0;
			tmp = tmp->next;
		}
		if (check_name(name) == 1)
		{
			new = ft_memalloc(sizeof(t_history));
			tmp->cursor = 0;
			tmp->next = new;
			new->prev = tmp;
			new->command = ft_strdup(name);
			new->next = NULL;
			new->cursor = 1;
		}
	}
}

t_history	*init_history(void)
{
	int			fd;
	t_history	*list;
	char		*line;

	if ((fd = open("/tmp/.history", O_RDWR | O_APPEND | O_CREAT, S_IRUSR
		| S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		exit_term(0);
	if ((get_next_line(fd, &line)) != 0)
	{
		list = init_list(line);
		free(line);
	}
	else
		list = init_list(" ");
	while (get_next_line(fd, &line) != 0)
	{
		add_front_history(&list, line);
		free(line);
	}
	close(fd);
	return (list);
}
