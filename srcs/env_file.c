/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 23:46:11 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:52 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int			print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i]);
		ft_putchar('\n');
		i++;
	}
	return (1);
}

char		**clearenvz(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_memdel((void **)&env[i++]);
	}
	return (env);
}

char		**get_new_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * 500);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char		**get_new_av(char **av, int decallage)
{
	int		i;
	int		j;
	char	**new_av;

	i = 0;
	while (av[i])
		i++;
	new_av = (char **)malloc(sizeof(char *) * (i - decallage + 2));
	i = decallage;
	j = 0;
	while (av[i])
	{
		new_av[j] = ft_strdup(av[i]);
		j++;
		i++;
	}
	new_av[j] = NULL;
	return (new_av);
}

char		**get_new_replace(char **av, int decallage, char *new)
{
	int		i;
	int		j;
	char	**new_av;

	i = 0;
	while (av[i])
		i++;
	new_av = (char **)malloc(sizeof(char *) * (i - decallage + 2));
	i = decallage;
	new_av[0] = ft_strdup(new);
	j = 1;
	while (av[i])
	{
		new_av[j] = ft_strdup(av[i]);
		j++;
		i++;
	}
	new_av[j] = NULL;
	return (new_av);
}
