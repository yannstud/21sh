/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 10:31:42 by amottier          #+#    #+#             */
/*   Updated: 2018/04/18 14:16:30 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		delete_env(t_env **env, t_env *prev, t_env *tmp, t_cmd *cmd)
{
	if (!(prev))
	{
		if (tmp->next)
		{
			*env = tmp->next;
			cmd->enva = tmp->next;
			free_env(tmp->value, tmp->name, tmp);
			tmp = NULL;
		}
		else
		{
			free_env(tmp->value, tmp->name, *env);
			cmd->enva = NULL;
			*env = NULL;
		}
	}
	else
	{
		prev->next = tmp->next;
		free_env(tmp->value, tmp->name, tmp);
	}
}

int			ft_unsetenv(t_env **env, char **tabz, int i, t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = cmd->enva;
	prev = NULL;
	if (!(tmp))
		return (0);
	while (ft_strcmp(tmp->name, tabz[i]) != 0)
	{
		prev = tmp;
		if (!(tmp->next))
			return (0);
		tmp = tmp->next;
	}
	delete_env(env, prev, tmp, cmd);
	return (0);
}

int			ft_clearenv(t_env **env)
{
	t_env		*tmp;

	if (!(get_list_size(*env)))
		return (0);
	while ((*env))
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->name);
		free(tmp->value);
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

int			ft_unsetenvloop(t_env **env, char **tabz, t_cmd *cmd)
{
	int i;

	i = 1;
	if (!(tabz[1]))
		return (0);
	while (tabz[i])
	{
		ft_unsetenv(env, tabz, i, cmd);
		i++;
	}
	return (0);
}
