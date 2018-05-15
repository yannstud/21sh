/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 10:58:44 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:59:04 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		add_to_env(t_env **head, int *index)
{
	t_env		*element;
	char		**tabz;
	t_env		*tmp;
	extern char **environ;

	tmp = NULL;
	tabz = ft_strsplit(environ[*index], '=');
	if (!(element = malloc(sizeof(t_env))))
		return ;
	element->name = tabz[0];
	element->value = tabz[1];
	element->next = NULL;
	if (!(*head))
		*head = element;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = element;
	}
	++(*index);
	free(tabz);
}

t_env		*parse_env(void)
{
	t_env			*head;
	int				index;
	extern char		**environ;

	head = NULL;
	index = 0;
	while (environ[index])
	{
		add_to_env(&head, &index);
	}
	if (!(index))
		return (minimum_env());
	return (head);
}

t_env		*minimum_env(void)
{
	t_env	*element;
	char	cwd[1024];

	if (!(element = malloc(sizeof(t_env))))
		return (NULL);
	element->name = ft_strdup("PWD");
	element->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	element->next = NULL;
	return (element);
}

int			get_list_size(t_env *li)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = li;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char		**get_env_char(t_env *env)
{
	int		len;
	char	**env_char;
	t_env	*tmp;
	int		i;

	i = 0;
	len = get_list_size(env);
	if (!(env_char = malloc(sizeof(char*) * (len + 2))))
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (!(env_char[i] = malloc(sizeof(char) * ((ft_strlen(tmp->name)
						+ ft_strlen(tmp->value) + 3)))))
			return (NULL);
		env_char[i] = ft_strjoin(tmp->name, "=");
		env_char[i] = ft_strjoin(env_char[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	env_char[i] = NULL;
	return (env_char);
}
