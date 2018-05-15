/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 10:02:24 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 12:15:02 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

static const t_token_type g_next[25][25][1] =
{
	[TOKEN_NONE] = {
		[TOKEN_BLANK] = {1},
		[TOKEN_WORD] = {1},
		[TOKEN_IO_NUMBER] = {1},
		[TOKEN_SQUOTE] = {1},
		[TOKEN_DQUOTE] = {1},
		[TOKEN_BQUOTE] = {1},
		[TOKEN_NEWLINE] = {1},
		[TOKEN_SEMI] = {1},
		[TOKEN_GREAT] = {1},
		[TOKEN_LESS] = {1},
		[TOKEN_DLESS] = {1},
		[TOKEN_DGREAT] = {1}
	},
	[TOKEN_DLESS] = {
		[TOKEN_BLANK] = {1},
		[TOKEN_WORD] = {1},
		[TOKEN_IO_NUMBER] = {1},
		[TOKEN_SQUOTE] = {1},
		[TOKEN_DQUOTE] = {1},
		[TOKEN_BQUOTE] = {1},
		[TOKEN_NEWLINE] = {0}
	},
	[TOKEN_WORD] = {
		[TOKEN_BLANK] = {1},
		[TOKEN_NEWLINE] = {1},
		[TOKEN_WORD] = {1},
		[TOKEN_SQUOTE] = {1},
		[TOKEN_BQUOTE] = {1},
		[TOKEN_DQUOTE] = {1},
		[TOKEN_PIPE] = {1},
		[TOKEN_LESSGREAT] = {1},
		[TOKEN_AND] = {1},
		[TOKEN_SEMI] = {1},
		[TOKEN_IO_NUMBER] = {1},
		[TOKEN_DLESS] = {1},
		[TOKEN_DGREAT] = {1},
		[TOKEN_OR_IF] = {1},
		[TOKEN_AND_IF] = {1},
		[TOKEN_LESSAND] = {1},
		[TOKEN_GREATAND] = {1}
	},
	[TOKEN_PIPE] = {
		[TOKEN_BLANK] = {1},
		[TOKEN_WORD] = {1},
		[TOKEN_NEWLINE] = {1},
		[TOKEN_SQUOTE] = {1},
		[TOKEN_BQUOTE] = {1},
		[TOKEN_DQUOTE] = {1},
		[TOKEN_LESSGREAT] = {1},
		[TOKEN_IO_NUMBER] = {1},
		[TOKEN_DLESS] = {1},
		[TOKEN_DGREAT] = {1},
		[TOKEN_LESSAND] = {1},
		[TOKEN_GREATAND] = {1}
	},
	[TOKEN_SEMI] = {
		[TOKEN_BLANK] = {1},
		[TOKEN_WORD] = {1},
		[TOKEN_SQUOTE] = {1},
		[TOKEN_BQUOTE] = {1},
		[TOKEN_DQUOTE] = {1},
		[TOKEN_LESSGREAT] = {1},
		[TOKEN_IO_NUMBER] = {1},
		[TOKEN_DLESS] = {1},
		[TOKEN_DGREAT] = {1},
		[TOKEN_LESSAND] = {1},
		[TOKEN_GREATAND] = {1},
		[TOKEN_NEWLINE] = {1}
	},
	[TOKEN_OR_IF] = {
		[TOKEN_BLANK] = {1},
		[TOKEN_WORD] = {1},
		[TOKEN_SQUOTE] = {1},
		[TOKEN_BQUOTE] = {1},
		[TOKEN_DQUOTE] = {1},
		[TOKEN_LESSGREAT] = {1},
		[TOKEN_IO_NUMBER] = {1},
		[TOKEN_DLESS] = {1},
		[TOKEN_DGREAT] = {1},
		[TOKEN_LESSAND] = {1},
		[TOKEN_GREATAND] = {1}
	}
};

t_token_type		get_type(t_token_type type)
{
	if (type == TOKEN_WORD || type == TOKEN_BQUOTE
		|| type == TOKEN_DQUOTE || type == TOKEN_SQUOTE
		|| type == TOKEN_IO_NUMBER || type == TOKEN_NEWLINE)
		return (TOKEN_WORD);
	else if (type == TOKEN_DLESS || type == TOKEN_DGREAT
		|| type == TOKEN_LESSAND || type == TOKEN_GREATAND
		|| type == TOKEN_ANDGREAT || type == TOKEN_LESSGREAT
		|| type == TOKEN_LESS || type == TOKEN_GREAT)
		return (TOKEN_DLESS);
	else if (type == TOKEN_OR_IF || type == TOKEN_AND_IF || type == TOKEN_AND)
		return (TOKEN_OR_IF);
	return (type);
}

int					check_first(t_token *head)
{
	if (!(head))
		return (1);
	while (head->next && head->type == TOKEN_BLANK)
		head = head->next;
	if (!(g_next[TOKEN_NONE][head->type][0]))
	{
		parsing_error(head->str);
		return (0);
	}
	else
		return (1);
}

int					check_last(t_token *head)
{
	t_token		*last;

	if (!(head))
		return (1);
	last = NULL;
	while (head)
	{
		if (head->type != TOKEN_BLANK)
			last = head;
		head = head->next;
	}
	if (last && !(g_next[get_type(last->type)][TOKEN_NEWLINE][0]))
	{
		parsing_error(last->str);
		return (0);
	}
	return (1);
}

int					check_middle(t_token *head)
{
	t_token *nxt;

	if (!(head) || !(head->next))
		return (1);
	while (head->next && head->type == TOKEN_BLANK)
		head = head->next;
	nxt = head->next;
	while (head->next)
	{
		while (nxt->next && nxt->type == TOKEN_BLANK)
			nxt = nxt->next;
		if (!(g_next[get_type(head->type)][get_type(nxt->type)][0]))
		{
			parsing_error(head->str);
			return (0);
		}
		head = nxt;
		nxt = nxt->next;
	}
	return (1);
}

int					parsing(t_token *head)
{
	return (check_unsopprted_tokens(head) && check_first(head)
			&& check_last(head) && check_middle(head));
}
