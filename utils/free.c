/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 07:57:11 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:59:02 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void	free_tabz(char **tabz)
{
	int i;

	i = 0;
	while (tabz[i])
	{
		free(tabz[i]);
		tabz[i] = NULL;
		i++;
	}
	free(tabz);
}

void	free_env(char *value, char *name, t_env *env)
{
	if (value)
		free(value);
	free(name);
	free(env);
}

void	free_token(t_token *elem)
{
	t_token		*tmp;
	t_token		*tmp2;

	if (!(elem))
		return ;
	tmp = elem;
	while (tmp)
	{
		free(tmp->str);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void	free_heredoc(t_heredoc *elem)
{
	t_heredoc		*tmp;
	t_heredoc		*tmp2;

	if (!(elem))
		return ;
	tmp = elem;
	while (tmp)
	{
		free(tmp->content);
		free(tmp->end_word);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}
