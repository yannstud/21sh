/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 10:36:30 by amottier          #+#    #+#             */
/*   Updated: 2018/04/27 11:48:18 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

char		*get_value(t_env *env, char *name)
{
	t_env	*tmp;
	char	cwd[1024];

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	if (ft_strcmp(name, "PWD") == 0)
		return (ft_strdup(getcwd(cwd, sizeof(cwd))));
	ft_putstr("21sh: cd: ");
	ft_putstr(name);
	ft_putstr(" not set\n");
	return (NULL);
}

int			edit_value(char *name, char *value, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	add_element(prev, env, name, value);
	return (1);
}

int			change_dir(char *path, t_env **env)
{
	DIR				*dirp;
	char			cwd[1024];
	char			*pwd;
	struct stat		path_stat;
	int				stat_res;

	stat_res = lstat(path, &path_stat);
	dirp = opendir(path);
	if (dirp)
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
			edit_value("OLDPWD", pwd, &(*env));
		}
		chdir(path);
		pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
		edit_value("PWD", pwd, &(*env));
		closedir(dirp);
	}
	else
		print_err_cd(stat_res, path, path_stat);
	return (1);
}

int			cd_home(t_env **env, char **tabz, char *new_path, char *folder)
{
	if (!tabz[1])
	{
		if (!(get_value(*env, "HOME")))
			return (1);
		new_path = get_value(*env, "HOME");
		change_dir(new_path, env);
	}
	else if (tabz[1][0] == '~')
	{
		if (!(get_value(*env, "HOME")))
			return (1);
		folder = ft_strsub(tabz[1], 1, ft_strlen(tabz[1]) - 1);
		new_path = ft_strjoin(get_value(*env, "HOME"), folder);
		change_dir(new_path, env);
		free(new_path);
		free(folder);
	}
	return (1);
}

int			ft_cd(t_env **env, char **tabz)
{
	char			*new_path;
	char			*folder;

	new_path = NULL;
	folder = NULL;
	if (!tabz[1] || tabz[1][0] == '~')
		cd_home(env, tabz, new_path, folder);
	else if (tabz[1][0] == '/')
		change_dir(tabz[1], env);
	else if (ft_strcmp(tabz[1], "-") == 0)
	{
		if (!(get_value(*env, "OLDPWD")))
			return (1);
		ft_putendl(get_value(*env, "OLDPWD"));
		change_dir(get_value(*env, "OLDPWD"), env);
	}
	else
	{
		folder = add_slash(get_value(*env, "PWD"));
		new_path = ft_strjoin(folder, tabz[1]);
		change_dir(new_path, env);
		free(folder);
		free(new_path);
	}
	return (0);
}
