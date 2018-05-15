/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 15:17:15 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:58:57 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void	handle_blank(char **cmd, t_token **head)
{
	while (**cmd && (get_ascii_type(**cmd) == CHAR_BLANK))
		(*cmd)++;
	add_token(head, TOKEN_BLANK, ft_strdup(" "));
}

void	handle_semicolon(char **cmd, t_token **head)
{
	add_token(head, TOKEN_SEMI, ft_strdup(";"));
	(*cmd)++;
}

void	handle_dquote(char **cmd, t_token **head, char *tmp, int start)
{
	(*cmd)++;
	while (**cmd && !(get_ascii_type(**cmd) == CHAR_DQUOTE))
		(*cmd)++;
	if (!(**cmd))
		add_token(head, TOKEN_DQUOTE, ft_strdup("\"unclosed\""));
	add_token(head, TOKEN_DQUOTE, crop_str(tmp, *cmd, start, 1));
}

void	handle_squote(char **cmd, t_token **head, char *tmp, int start)
{
	(*cmd)++;
	while (**cmd && !(get_ascii_type(**cmd) == CHAR_SQUOTE))
		(*cmd)++;
	if (!(**cmd))
		add_token(head, TOKEN_DQUOTE, ft_strdup("\'unclosed\'"));
	add_token(head, TOKEN_SQUOTE, crop_str(tmp, *cmd, start, 1));
}

void	handle_newline(char **cmd, t_token **head)
{
	add_token(head, TOKEN_NEWLINE, ft_strdup("\n"));
	(*cmd)++;
}
