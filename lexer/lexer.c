/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 15:17:15 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:58:57 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void	handle_switch(t_token **head, char **cmd, int start, char *tmp)
{
	int i;

	i = get_ascii_type(**cmd);
	if (i == CHAR_BLANK)
		handle_blank(&(*cmd), head);
	else if (i == CHAR_SEMICOLON)
		handle_semicolon(&(*cmd), head);
	else if (i == CHAR_NEWLINE)
		handle_newline(&(*cmd), head);
	else if (i == CHAR_PIPE)
		handle_pipe(&(*cmd), head);
	else if (i == CHAR_AND)
		handle_and(&(*cmd), head);
	else if (i == CHAR_LETTER)
		handle_word(&(*cmd), head, tmp, start);
	else if (i == CHAR_DIGIT)
		handle_digit(&(*cmd), head, tmp, start);
	else if (i == CHAR_COMPARE && **cmd == '>')
		handle_compare_great(&(*cmd), head);
	else if (i == CHAR_COMPARE && **cmd == '<')
		handle_compare_less(&(*cmd), head);
	else
		(*cmd)++;
}

void	get_token(t_token **head, char *cmd)
{
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	tmp = cmd;
	start = 0;
	while (*cmd)
	{
		i = get_ascii_type(*cmd);
		start = ft_strlen(tmp) - ft_strlen(cmd);
		if (i == CHAR_DQUOTE)
			handle_dquote(&cmd, head, tmp, start);
		if (i == CHAR_SQUOTE)
			handle_squote(&cmd, head, tmp, start);
		handle_switch(head, &cmd, start, tmp);
	}
}
