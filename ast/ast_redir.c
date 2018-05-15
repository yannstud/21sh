/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 09:43:21 by amottier          #+#    #+#             */
/*   Updated: 2018/04/27 10:45:51 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

t_token			*has_redirection(t_token *head)
{
	t_token *tmp;

	tmp = head;
	while (tmp && tmp->next)
	{
		if (tmp->type >= TOKEN_GREAT && tmp->type <= TOKEN_GREATAND)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static t_token	*get_next_word(t_token *tkn)
{
	t_token *tmp;

	if (tkn->type == TOKEN_WORD || tkn->type == TOKEN_IO_NUMBER)
	{
		return (tkn);
	}
	while (tkn && tkn->next && tkn->type == TOKEN_BLANK)
	{
		tmp = tkn->next;
		free(tkn->str);
		free(tkn);
		tkn = tmp;
	}
	if (tkn->type == TOKEN_WORD || tkn->type == TOKEN_IO_NUMBER)
		return (tkn);
	return (NULL);
}

t_token			*handle_redir_left(t_token *node)
{
	t_token		*le;
	t_token		*tmp;
	char		*fullname;

	if ((le = node->prev))
		if (le->type == TOKEN_IO_NUMBER && node->type != TOKEN_ANDGREAT)
		{
			if (!(fullname = malloc(sizeof(char) * (ft_strlen(le->str)
				+ ft_strlen(node->str) + 1))))
				return (NULL);
			ft_strcpy(fullname, le->str);
			ft_strcat(fullname, node->str);
			free(node->str);
			free(le->str);
			node->str = fullname;
			node->fd_from = ft_atoi(node->str);
			tmp = le;
			le = le->prev;
			free(tmp);
		}
	return (le);
}

t_token			*handle_redir_right(t_token *node)
{
	t_token		*ri;
	t_token		*tmp;
	char		*fullname;

	if ((ri = node->next))
		if (ri->type == TOKEN_IO_NUMBER || ((ri = get_next_word(ri))))
		{
			if (!(fullname = malloc(sizeof(char) * (ft_strlen(node->str)
				+ ft_strlen(ri->str) + 1))))
				return (NULL);
			ft_strcpy(fullname, node->str);
			ft_strcat(fullname, ri->str);
			free(node->str);
			node->str = fullname;
			if (ri->type == TOKEN_IO_NUMBER && (node->type == TOKEN_GREATAND
				|| node->type == TOKEN_LESSAND))
				node->fd_to = ft_atoi(ri->str);
			else
				node->filename = ft_strdup(ri->str);
			free(ri->str);
			tmp = ri;
			ri = ri->next;
			free(tmp);
		}
	return (ri);
}

t_btree			*ast_redirection(t_token *node, t_token *head)
{
	t_token *le;
	t_token *ri;

	le = handle_redir_left(node);
	ri = handle_redir_right(node);
	node->prev = NULL;
	node->next = NULL;
	if (le)
		le->next = ri;
	else
		head = ri;
	if (ri)
		ri->prev = le;
	return (join_tree(new_tree(head), NULL, node));
}
