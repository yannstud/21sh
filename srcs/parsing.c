/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:49:19 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:59:05 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

char		**check_param(char **env)
{
	int		i;
	char	*ret;
	char	**path_tab;
	char	**line;
	char	*memchrret;

	i = 0;
	if (env)
		while (env[i])
		{
			line = ft_strsplit(env[i], '=');
			if (ft_strcmp(line[0], "PATH") == 0)
			{
				if ((memchrret = ft_memchr(env[i], '=', 10)) == NULL)
					return (NULL);
				ret = ft_strdup(memchrret);
				path_tab = ft_strsplit(ret, ':');
				ft_memdel((void **)&ret);
				free_double_tab(line);
				return (path_tab);
			}
			free_double_tab(line);
			i++;
		}
	return (NULL);
}

char		*getpath(char **path, char *line)
{
	int			i;
	char		*tmp;
	char		*new_path;
	struct stat	sb;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		new_path = ft_strjoin(tmp, line);
		free(tmp);
		if (lstat(new_path, &sb) != -1)
			return (new_path);
		else if (new_path)
			free(new_path);
		i++;
	}
	return (0);
}

char		**init_env(char **envp)
{
	char	**env;
	int		i;

	if (!(env = (char **)malloc(sizeof(char *) * 500)))
		return (NULL);
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

void		change_pwd(char *old_pwd, char *new_pwd, char **env)
{
	int		i;
	char	**line;

	i = -1;
	while (env[++i])
	{
		line = ft_strsplit(env[i], '=');
		if (ft_strcmp(line[0], "PWD") == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", new_pwd);
			free(new_pwd);
		}
		else if (ft_strcmp(line[0], "OLDPWD") == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", old_pwd);
			free(old_pwd);
		}
		free_double_tab(line);
	}
}

char		*get_old_pwd(char **env)
{
	int		i;
	char	**line;
	char	*ret;

	ret = NULL;
	i = 0;
	while (env[i])
	{
		line = ft_strsplit(env[i], '=');
		if (line[1] && ft_strcmp(line[0], "OLDPWD") == 0)
		{
			ret = ft_strdup(line[1]);
			free_double_tab(line);
			return (ret);
		}
		free_double_tab(line);
		i++;
	}
	ft_putstr_fd("21sh: cd: OLDPWD not set\n", 2);
	return (NULL);
}
