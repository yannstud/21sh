/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:47:46 by amottier          #+#    #+#             */
/*   Updated: 2018/04/27 11:33:06 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int		exec_write(t_btree *ast, t_env *env, int to_fork, t_cmd *cmd)
{
	int fd;
	int ret;

	if (ast->data->type == TOKEN_GREAT)
		fd = open_file(ast->data->filename, 0, 0);
	else
		fd = open_file(ast->data->filename, 1, 0);
	if (fd == -1)
		return (0);
	if (ast->data->fd_from == -1)
		ast->data->fd_from = 1;
	dup2(fd, ast->data->fd_from);
	ret = exec_recursive(ast->left, env, to_fork, cmd);
	close(fd);
	return (ret);
}

int		exec_andwrite(t_btree *ast, t_env *env, int to_fork, t_cmd *cmd)
{
	int fd;
	int ret;

	if ((fd = open_file(ast->data->filename, 0, 0)) == -1)
		return (0);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	ret = exec_recursive(ast->left, env, to_fork, cmd);
	close(fd);
	return (ret);
}

int		exec_write_and(t_btree *ast, t_env *env, int to_fork, t_cmd *cmd)
{
	int		fd;
	int		ret;
	int		fd_tmp;

	if (ast->data->filename && ft_strcmp(ast->data->filename, "-"))
	{
		if ((fd = open_file(ast->data->filename, 0, 0)) == -1)
			return (0);
	}
	else if (ast->data->filename && !(ft_strcmp(ast->data->filename, "-")))
		return (exec_write_and_closed(ast, env, to_fork, cmd));
	else
	{
		fd = ast->data->fd_to;
		if ((fd_tmp = dup(fd)) == -1)
			return (err_no_fd(fd));
		close(fd_tmp);
	}
	if (ast->data->fd_from == -1)
		dup_both(fd);
	else
		dup2(fd, ast->data->fd_from);
	ret = exec_recursive(ast->left, env, to_fork, cmd);
	close(fd);
	return (ret);
}
