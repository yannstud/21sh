/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 10:25:46 by amottier          #+#    #+#             */
/*   Updated: 2018/04/18 14:14:33 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

int			add_edit_env(t_env **env, t_env *tmp, t_env *element)
{
	t_env *prev;

	if (tmp)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->name, element->name) == 0)
			{
				free(tmp->value);
				tmp->value = element->value;
				free_env(NULL, element->name, element);
				return (0);
			}
			prev = tmp;
			tmp = tmp->next;
		}
		prev->next = element;
	}
	else
		*env = element;
	return (0);
}

int			ft_setenv(t_env **env, char **tabz, int i)
{
	t_env	*tmp;
	t_env	*element;
	char	**split;

	tmp = *env;
	if (tabz[i] && ft_strchr(tabz[i], '='))
	{
		if (!(split = split_setenv(tabz[i])))
			return (0);
		if (!(element = malloc(sizeof(t_env))))
			return (0);
		element->name = split[0];
		element->value = split[1];
		free(split);
		element->next = NULL;
		return (add_edit_env(&(*env), tmp, element));
	}
	return (0);
}

int			ft_setenvloop(t_env **env, char **tabz, int i, t_cmd *cmd)
{
	(void)env;
	if (!tabz[i])
	{
		print_env_list(cmd->enva);
		return (0);
	}
	while (tabz[i])
	{
		ft_setenv(&(cmd->enva), tabz, i);
		i++;
	}
	return (0);
}
