/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 15:17:15 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 12:05:42 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

static char		*get_token_name2(t_token_type type)
{
	if (type == TOKEN_GREAT)
		return ("GREAT");
	else if (type == TOKEN_DGREAT)
		return ("DGREAT");
	else if (type == TOKEN_LESSGREAT)
		return ("LESSGREAT");
	else if (type == TOKEN_GREATAND)
		return ("GREATAND");
	else if (type == TOKEN_DLESS)
		return ("DLESS");
	else if (type == TOKEN_LESSAND)
		return ("LESSAND");
	else if (type == TOKEN_SEMI)
		return ("SEMI");
	else if (type == TOKEN_DQUOTE)
		return ("DQUOTE");
	else if (type == TOKEN_SQUOTE)
		return ("SQUOTE");
	return ("UNDEFINED");
}

static char		*get_token_name(t_token_type type)
{
	if (type == TOKEN_BLANK)
		return ("BLANK");
	else if (type == TOKEN_WORD)
		return ("WORD");
	else if (type == TOKEN_IO_NUMBER)
		return ("IO_NUMBER");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_OR_IF)
		return ("OR_IF");
	else if (type == TOKEN_AND_IF)
		return ("AND_IF");
	else if (type == TOKEN_AND)
		return ("AND");
	else if (type == TOKEN_ANDGREAT)
		return ("ANDGREAT");
	else if (type == TOKEN_LESS)
		return ("LESS");
	else
		return (get_token_name2(type));
}

void			print_tokens(t_token *head)
{
	t_token *tmp;

	tmp = head;
	while (tmp)
	{
		ft_putstr("<");
		ft_putstr(tmp->str);
		ft_putstr("> => TOKEN_");
		ft_putendl(get_token_name(tmp->type));
		tmp = tmp->next;
	}
}
