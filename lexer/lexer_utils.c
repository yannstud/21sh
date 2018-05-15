/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 15:17:15 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 12:06:01 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int			get_ascii_type(int c)
{
	if (c >= '0' && c <= '9')
		return (CHAR_DIGIT);
	else if (c == ' ' || c == '\t')
		return (CHAR_BLANK);
	else if (c == '\'')
		return (CHAR_SQUOTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == ';')
		return (CHAR_SEMICOLON);
	else if (c == '&')
		return (CHAR_AND);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '<' || c == '>')
		return (CHAR_COMPARE);
	else if (c == '|')
		return (CHAR_PIPE);
	else
		return (CHAR_LETTER);
}

t_token		*new_elem(char *str, t_char_type type)
{
	t_token *elem;

	if (!(elem = malloc(sizeof(t_token))))
		return (NULL);
	elem->len = ft_strlen(str);
	elem->str = str;
	elem->type = type;
	elem->fd_from = -1;
	elem->fd_to = 1;
	elem->next = NULL;
	elem->prev = NULL;
	elem->filename = NULL;
	return (elem);
}

void		add_token(t_token **head, t_char_type type, char *str)
{
	t_token *tmp;
	t_token *elem;
	t_token *prev;

	prev = NULL;
	if (!(elem = new_elem(str, type)))
		return ;
	if (!(*head))
	{
		*head = elem;
		return ;
	}
	tmp = *head;
	prev = tmp;
	while (tmp->next)
	{
		tmp = tmp->next;
		prev = tmp;
	}
	elem->prev = prev;
	tmp->next = elem;
}

char		*crop_str(char *tmp, char *cmd, int start, int diff)
{
	return (ft_strsub(tmp, start,
		(ft_strlen(tmp) - ft_strlen(cmd) - start) + diff));
}

void		lexer_error(void)
{
	ft_putendl_fd("Lexer Error\n", 2);
	exit(0);
}
