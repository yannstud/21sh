/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 14:17:41 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:59:00 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

char		**get_path(t_env *env)
{
	t_env		*tmp;

	tmp = env;
	if (!(env))
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			return (ft_strsplit(tmp->value, ':'));
		tmp = tmp->next;
	}
	return (NULL);
}

char		*add_slash(char *full_path)
{
	int len;

	len = ft_strlen(full_path);
	if (full_path[len - 1] != '/')
	{
		if (!(full_path = ft_strjoin(full_path, "/")))
			return (NULL);
	}
	else
	{
		if (!(full_path = ft_strdup(full_path)))
			return (NULL);
	}
	return (full_path);
}

void		add_element(t_env *prev, t_env **env, char *name, char *value)
{
	t_env	*element;

	if (!(element = malloc(sizeof(t_env))))
		return ;
	element->name = ft_strdup(name);
	element->value = ft_strdup(value);
	free(value);
	value = NULL;
	if (!(*env))
	{
		element->next = NULL;
		*env = element;
	}
	else
	{
		element->next = NULL;
		prev->next = element;
	}
}

char		**split_setenv(char *str)
{
	char	**split;
	int		len;

	len = 0;
	if (!(split = ft_strsplit(str, '=')))
	{
		free_tabz(split);
		return (NULL);
	}
	while (split[len])
		len++;
	if (len < 1 || !split[0] || str[0] == '=')
	{
		free_tabz(split);
		return (NULL);
	}
	return (split);
}

char		*realloc_str(char *str1, char *str2)
{
	char *tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(str1)
				+ ft_strlen(str2) + 1));
	ft_strcpy(tmp, str1);
	ft_strcat(tmp, str2);
	free(str1);
	str1 = tmp;
	return (str1);
}
