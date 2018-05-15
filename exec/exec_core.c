/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 07:39:34 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 17:42:19 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int			run_cmd(char *path, char **tabz, t_env *env, int to_fork)
{
	pid_t pid;

	if (to_fork)
	{
		if ((pid = fork()) == -1)
			return (1);
		if (pid == 0)
		{
			execve(path, tabz, get_env_char(env));
			ft_putstr_fd("error exec\n", 2);
		}
		ft_pid(pid, 1);
		wait(&pid);
		singlexex(WIFSIGNALED(pid));
		return (WEXITSTATUS(pid));
	}
	else
	{
		execve(path, tabz, get_env_char(env));
		ft_putstr_fd("error exec2\n", 2);
	}
	return (0);
}

char		*get_executable(char *name, char **path)
{
	int				i;
	char			*folder_name;
	char			*exec_path;

	i = 0;
	folder_name = NULL;
	exec_path = NULL;
	if (!(path))
		return (NULL);
	while (path[i])
	{
		if ((exec_path = browse_dir(name, path[i], folder_name)))
		{
			free_tabz(path);
			return (exec_path);
		}
		i++;
	}
	free_tabz(path);
	return (NULL);
}

int			bin_exist(char *path)
{
	struct stat		st;
	int				res;

	res = stat(path, &st);
	if (res == 0 && st.st_mode & S_IXUSR && S_ISREG(st.st_mode))
		return (1);
	else
		return (0);
}

int			not_bultin(char **tabz, t_env **env, int to_fork)
{
	char	*exec_path;
	int		retv;

	exec_path = NULL;
	retv = 0;
	if (bin_exist(tabz[0]))
		exec_path = ft_strdup(tabz[0]);
	else
		exec_path = get_executable(tabz[0], get_path(*env));
	if (exec_path)
	{
		retv = run_cmd(exec_path, tabz, *env, to_fork);
		free(exec_path);
	}
	else
	{
		err_no_cmd(tabz[0]);
		retv = 1;
	}
	return (retv);
}

char		*browse_dir(char *name,
						char *path, char *folder_name)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*exec_path;

	if (!(dirp = opendir(path)))
		return (NULL);
	folder_name = add_slash(path);
	while ((dp = readdir(dirp)) != NULL)
		if (ft_strcmp(name, dp->d_name) == 0)
		{
			exec_path = ft_strjoin(folder_name, dp->d_name);
			closedir(dirp);
			free(folder_name);
			return (exec_path);
		}
	free(folder_name);
	closedir(dirp);
	return (NULL);
}
