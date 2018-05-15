/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:47:42 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:50 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int			back_to_olddir(char *old_pwd, char **env, char *pwd)
{
	char	*old;
	char	*new_pwd;

	getcwd(old_pwd, 500);
	if ((old = get_old_pwd(env)) == NULL)
		return (0);
	if (chdir(old) != -1)
	{
		new_pwd = ft_strnew(500);
		getcwd(new_pwd, 500);
		change_pwd(old_pwd, new_pwd, env);
		free(old);
		free(pwd);
		return (1);
	}
	return (0);
}

int			goto_dir(char *old_pwd, char **av, char *pwd, char **env)
{
	char *new_pwd;

	getcwd(old_pwd, 500);
	if (chdir(av[1]) != -1)
	{
		new_pwd = ft_strnew(500);
		getcwd(new_pwd, 500);
		free(pwd);
		change_pwd(old_pwd, new_pwd, env);
		return (1);
	}
	if (chdir(av[1]) == -1)
	{
		ft_putstr_fd("21sh: cd: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(" Permission denied\n", 2);
	}
	return (0);
}

int			cd_built(char **av, char *pwd, char **env)
{
	struct stat	sb;
	char		*old_pwd;

	old_pwd = ft_strnew(500);
	if (!av[1])
	{
		getcwd(old_pwd, 500);
		if (chdir(pwd) != -1)
		{
			change_pwd(old_pwd, pwd, env);
			return (1);
		}
	}
	else if (ft_strcmp(av[1], "-") == 0 &&
		back_to_olddir(old_pwd, env, pwd) == 1)
		return (1);
	else if (stat(av[1], &sb) != -1 &&
		goto_dir(old_pwd, av, pwd, env) == 1)
		return (1);
	else if (ft_strcmp(av[0], "cd") == 0 && stat(av[1], &sb) == -1)
		print_error_file(av[1]);
	free(old_pwd);
	free(pwd);
	return (0);
}

void		help_is_cd(char **line, char **av, char **env)
{
	char *ret;

	ret = ft_strdup(line[1]);
	free_double_tab(line);
	cd_built(av, ret, env);
}

int			is_cd(char **av, char **env)
{
	int		i;
	char	**line;

	i = -1;
	line = NULL;
	if (av[0] && ft_strcmp(av[0], "cd") == 0)
	{
		if (env)
		{
			while (env[++i])
			{
				if (!(line = ft_strsplit(env[i], '=')))
					return (0);
				if (line[0] && CM(line[0], "HOME") == 0 && CM(av[0], "cd") == 0)
				{
					help_is_cd(line, av, env);
					return (1);
				}
				free_double_tab(line);
			}
		}
		ft_putstr_fd("21sh : cd: HOME not set\n", 2);
		return (1);
	}
	return (0);
}
