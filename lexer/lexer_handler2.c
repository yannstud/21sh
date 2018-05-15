/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 15:17:15 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:58:56 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void	handle_pipe(char **cmd, t_token **head)
{
	char *str;

	str = *cmd;
	if (**cmd && *(str + 1) == '|')
	{
		add_token(head, TOKEN_OR_IF, ft_strdup("||"));
		(*cmd)++;
	}
	else
		add_token(head, TOKEN_PIPE, ft_strdup("|"));
	(*cmd)++;
}

void	handle_and(char **cmd, t_token **head)
{
	char *str;

	str = *cmd;
	if (**cmd && *(str + 1) == '&')
	{
		add_token(head, TOKEN_AND_IF, ft_strdup("&&"));
		(*cmd)++;
	}
	else if (**cmd && *(str + 1) == '>')
	{
		add_token(head, TOKEN_ANDGREAT, ft_strdup("&>"));
		(*cmd)++;
	}
	else
	{
		add_token(head, TOKEN_AND, ft_strdup("&"));
	}
	(*cmd)++;
}

void	handle_word(char **cmd, t_token **head, char *tmp, int start)
{
	while (**cmd && (get_ascii_type(**cmd) == CHAR_LETTER
				|| get_ascii_type(**cmd) == CHAR_DIGIT))
		(*cmd)++;
	add_token(head, TOKEN_WORD, crop_str(tmp, *cmd, start, 0));
}

void	handle_digit(char **cmd, t_token **head, char *tmp, int start)
{
	int letter;

	letter = 0;
	while (**cmd && ((get_ascii_type(**cmd) == CHAR_LETTER
				|| get_ascii_type(**cmd) == CHAR_DIGIT)))
	{
		if (get_ascii_type(**cmd) == CHAR_LETTER)
			letter++;
		(*cmd)++;
	}
	if (!(letter))
		add_token(head, TOKEN_IO_NUMBER, crop_str(tmp, *cmd, start, 0));
	else
		add_token(head, TOKEN_WORD, crop_str(tmp, *cmd, start, 0));
}
