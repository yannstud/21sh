/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:29:36 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:59:09 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		add_heredoc(t_cmd **cmd, int pos, char *end_word)
{
	t_heredoc *hd;
	t_heredoc *new_hd;

	new_hd = malloc(sizeof(t_heredoc));
	new_hd->position = pos;
	new_hd->end_word = ft_strdup(end_word);
	new_hd->content = NULL;
	new_hd->next = NULL;
	hd = (*cmd)->heredoc;
	if (!(hd))
	{
		(*cmd)->heredoc = new_hd;
		(*cmd)->heredoc1 = new_hd;
	}
	else
	{
		while (hd->next)
			hd = hd->next;
		hd->next = new_hd;
	}
	(*cmd)->heredoc_total++;
}

int			parse_heredoc(t_cmd **cmd)
{
	t_token	*tmp;
	char	*end_word;
	int		pos;

	pos = 0;
	tmp = (*cmd)->head;
	while (tmp->next)
	{
		if (tmp->type == TOKEN_DLESS)
		{
			tmp = tmp->next;
			while (tmp->type == TOKEN_BLANK)
				tmp = tmp->next;
			end_word = tmp->str;
			add_heredoc(cmd, pos, end_word);
			pos++;
		}
		if (tmp->next)
			tmp = tmp->next;
	}
	if (!(pos))
		(*cmd)->heredoc_mode = 2;
	return (pos);
}

int			last_is_oper(t_token *head, char *cmd)
{
	t_token *tmp;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->type == TOKEN_BLANK || tmp->type == TOKEN_NEWLINE)
		tmp = tmp->prev;
	if (tmp->type == TOKEN_PIPE || tmp->type == TOKEN_AND_IF ||
		tmp->type == TOKEN_AND || cmd[ft_strlen(cmd) - 1] == '\\')
		return (1);
	return (0);
}
