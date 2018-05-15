/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 10:16:06 by amottier          #+#    #+#             */
/*   Updated: 2018/04/27 10:50:23 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

char			**tabz_pocess(t_token *tkn, int i)
{
	char	**tabz;

	if (!(tabz = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (tkn)
	{
		if (tkn->type != TOKEN_BLANK)
		{
			if (tkn->type == TOKEN_DQUOTE || tkn->type == TOKEN_SQUOTE)
				tabz[i] = ft_strsub(tkn->str, 1, ft_strlen(tkn->str) - 2);
			else
				tabz[i] = ft_strdup(tkn->str);
			i++;
		}
		tkn = tkn->next;
	}
	tabz[i] = NULL;
	return (tabz);
}

char			**tabz_from_token(t_token *tkn)
{
	int			i;
	t_token		*tmp;

	i = 0;
	tmp = tkn;
	while (tmp)
	{
		if (tmp->type != TOKEN_BLANK)
			i++;
		tmp = tmp->next;
	}
	if (!(i))
		return (NULL);
	return (tabz_pocess(tkn, i));
}

int				exec(char **tabz, t_env *env, int to_fork, t_cmd *cmd)
{
	if (ft_strcmp(tabz[0], "env") == 0)
		return (ft_env(&env, tabz, cmd));
	else if (ft_strcmp(tabz[0], "echo") == 0)
		return (ft_echo(&env, tabz));
	else if (ft_strcmp(tabz[0], "setenv") == 0)
		return (ft_setenvloop(&env, tabz, 1, cmd));
	else if (ft_strcmp(tabz[0], "unsetenv") == 0)
		return (ft_unsetenvloop(&env, tabz, cmd));
	else if (ft_strcmp(tabz[0], "cd") == 0)
		return (ft_cd(&env, tabz));
	else if (ft_strcmp(tabz[0], "exit") == 0)
		return (ft_exit(tabz));
	else
		return (not_bultin(tabz, &env, to_fork));
}

int				start_exec(t_btree *ast, t_env *env, int to_fork, t_cmd *cmd)
{
	int		res;
	char	**tabz;

	if (!(tabz = tabz_from_token(ast->data)))
		return (0);
	res = exec(tabz, env, to_fork, cmd);
	free_tabz(tabz);
	return (res);
}

int				exec_recursive(t_btree *ast, t_env *env,
								int to_fork, t_cmd *cmd)
{
	if (!(ast))
		return (0);
	if (ast->data->type == TOKEN_SEMI)
		return (exec_semicolon(ast, env, cmd));
	else if (ast->data->type == TOKEN_AND_IF)
		return (exec_and(ast, env, cmd));
	else if (ast->data->type == TOKEN_OR_IF)
		return (exec_or(ast, env, cmd));
	else if (ast->data->type == TOKEN_PIPE)
		return (exec_pipe(ast, env, cmd));
	else if (ast->data->type == TOKEN_GREAT || ast->data->type == TOKEN_DGREAT)
		return (exec_write(ast, env, to_fork, cmd));
	else if (ast->data->type == TOKEN_ANDGREAT)
		return (exec_andwrite(ast, env, to_fork, cmd));
	else if (ast->data->type == TOKEN_LESSAND)
		return (exec_read_and(ast, env, to_fork, cmd));
	else if (ast->data->type == TOKEN_GREATAND)
		return (exec_write_and(ast, env, to_fork, cmd));
	else if (ast->data->type == TOKEN_LESS)
		return (exec_read(ast, env, to_fork, cmd));
	else if (ast->data->type == TOKEN_DLESS)
		return (exec_heredoc(ast, env, to_fork, cmd));
	else
		return (start_exec(ast, env, to_fork, cmd));
}
