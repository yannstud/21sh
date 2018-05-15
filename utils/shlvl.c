/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 12:29:08 by amottier          #+#    #+#             */
/*   Updated: 2018/04/25 12:40:42 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

static char		*get_value_env(t_env **env, char *name)
{
	t_env		*tmp;

	tmp = *env;
	if (!(tmp))
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static void		shlvl_reset_warning(void)
{
	ft_putstr_fd("21sh: warning: shell level (1874919424)", 2);
	ft_putstr_fd(" too high, resetting to 1\n", 2);
}

int				is_digit_only(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

void			increase_shlvl(t_env **env)
{
	char	*str;
	int		lvl;
	char	**tabz;

	lvl = 0;
	str = get_value_env(env, "SHLVL");
	if (!(tabz = malloc(sizeof(char*) * 2))
		|| !(tabz[0] = malloc(sizeof(char) * 17)))
		return ;
	ft_strcpy(tabz[0], "SHLVL=");
	tabz[1] = NULL;
	if (str && (lvl = ft_atoi(str)) &&
		(lvl < 1874919424) && is_digit_only(str))
	{
		str = ft_itoa(++lvl);
		ft_strcat(tabz[0], str);
		free(str);
	}
	else
		ft_strcat(tabz[0], "1");
	if (lvl >= 1874919424)
		shlvl_reset_warning();
	ft_setenv(env, tabz, 0);
	free_tabz(tabz);
}

int				singlexex(int i)
{
	static int tmp;

	if (i != 2)
		tmp = i;
	return (tmp);
}
