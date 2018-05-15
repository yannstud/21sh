/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_operat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:20:29 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:59:20 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int				oper_priority(t_token *tkn)
{
	if (tkn->type == TOKEN_PIPE)
		return (1);
	else if (tkn->type >= TOKEN_OR_IF && tkn->type <= TOKEN_SEMI)
		return (2);
	return (0);
}

t_token			*has_operator(t_token *head)
{
	t_token		*tmp;
	t_token		*max_token;
	int			max;

	max = 0;
	tmp = head;
	max_token = NULL;
	while (tmp && tmp->prev)
	{
		tmp = tmp->prev;
		if (tmp->type >= TOKEN_PIPE)
		{
			if (oper_priority(tmp) > max)
			{
				max = oper_priority(tmp);
				max_token = tmp;
			}
		}
	}
	return (max_token);
}

t_btree			*ast_operator(t_token *node)
{
	t_token	*le;
	t_token	*ri;

	le = node->prev;
	ri = node->next;
	node->next = NULL;
	if (le)
	{
		le->next = NULL;
		while (le->prev)
			le = le->prev;
	}
	ri->prev = NULL;
	return (join_tree(new_tree(le), new_tree(ri), node));
}
