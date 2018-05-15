/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:49:24 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 13:09:16 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

t_env		*copy_env(t_env *env)
{
	t_env *tmp;
	t_env *elem;
	t_env *prev;
	t_env *head;

	prev = NULL;
	head = NULL;
	tmp = env;
	while (tmp)
	{
		if (!(elem = malloc(sizeof(t_env))))
			return (NULL);
		if (prev)
			prev->next = elem;
		else
			head = elem;
		elem->name = ft_strdup(tmp->name);
		elem->value = ft_strdup(tmp->value);
		elem->next = NULL;
		prev = elem;
		tmp = tmp->next;
	}
	return (head);
}

char		**realloc_tab(char **tabz, int i)
{
	int		total;
	int		len;
	char	**new_tabz;
	int		j;

	j = 0;
	total = 0;
	while (tabz[total])
		total++;
	len = total - i;
	if (!(new_tabz = malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	while (i < total)
	{
		new_tabz[j] = ft_strdup(tabz[i]);
		j++;
		i++;
	}
	new_tabz[j] = NULL;
	return (new_tabz);
}

void		free_tmp_env(t_env *tmp)
{
	t_env *tmp2;
	t_env *prev;

	tmp2 = tmp;
	while (tmp2)
	{
		prev = tmp2;
		tmp2 = tmp2->next;
		free(prev->value);
		free(prev->name);
		free(prev);
	}
}

int			process_tabs(char **tabz, t_env **tmp, int i)
{
	while (tabz[i])
	{
		if (ft_strcmp(tabz[i], "-i") == 0)
		{
			ft_clearenv(tmp);
			i++;
		}
		if (tabz[i] && ft_strchr(tabz[i], '='))
		{
			ft_setenv(tmp, tabz, i);
			i++;
		}
		else if (tabz[i] && ft_strcmp(tabz[i], "env") == 0)
			i++;
		else
			break ;
	}
	return (i);
}

int			ft_env(t_env **env, char **tabz, t_cmd *cmd)
{
	t_env	*tmp;
	int		i;
	char	**exe;

	*env = cmd->enva;
	i = 0;
	if (!tabz[1])
		return (print_env_list(*env));
	tmp = copy_env(*env);
	i++;
	i = process_tabs(tabz, &tmp, i);
	if (tabz[i])
	{
		exe = realloc_tab(tabz, i);
		not_bultin(exe, &tmp, 1);
		free_tabz(exe);
	}
	else
		print_env_list(tmp);
	free_tmp_env(tmp);
	return (0);
}
