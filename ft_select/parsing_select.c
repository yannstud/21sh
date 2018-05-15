/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 02:07:55 by ysalaun           #+#    #+#             */
/*   Updated: 2018/04/16 11:58:26 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

void		parsing_select_noargs(t_elem *alst)
{
	DIR				*rep;
	struct dirent	*file;
	t_elem			*new;

	new = NULL;
	if (!(rep = opendir(".")))
		return ;
	while ((file = readdir(rep)) != NULL)
	{
		if (file->d_name[0] != '.')
			add_front_select_list(&alst, new, file->d_name);
	}
	closedir(rep);
}

char		**parsing_help(int i, char **env)
{
	char	*str2;
	char	**tabz;
	int		j;

	i = 0;
	while (env[i])
		i++;
	i--;
	j = 0;
	while (j < i)
	{
		if ((ft_memcmp(env[j], "PATH", 4)) == 0)
			tabz = ft_strsplit(env[j], ':');
		j++;
	}
	i = 0;
	j = 5;
	str2 = ft_strnew(ft_strlen(tabz[0]));
	while (tabz[0][j])
		str2[i] = tabz[0][j++];
	free(tabz[0]);
	tabz[0] = ft_strdup(str2);
	free(str2);
	return (tabz);
}

t_elem		*parsing_path(char **env, char *str, t_line *line)
{
	int		i;
	char	**tabz;
	t_elem	*alst;

	alst = init_select_list();
	i = 0;
	if (line->count > 0)
	{
		if (str[line->count - 1] != ' ')
		{
			tabz = parsing_help(i, env);
			while (tabz[i])
				parsing_select(str, tabz[i++], alst);
			parsing_select(str, ".", alst);
			free_double_tab(tabz);
		}
		else
			parsing_select_noargs(alst);
	}
	return (alst);
}

void		parsing_select(char *str, char *name_rep, t_elem *alst)
{
	DIR				*rep;
	struct dirent	*file;
	t_elem			*new;
	char			**tabz;
	int				i;

	new = NULL;
	if (!(rep = opendir(name_rep)))
		return ;
	tabz = ft_split_whitespaces(str);
	if (!(tabz[0]))
		return ;
	i = 0;
	while (tabz[i])
		i++;
	i--;
	file = readdir(rep);
	while ((file = readdir(rep)) != NULL)
	{
		if (ft_memcmp(file->d_name, tabz[i], ft_strlen(tabz[i])) == 0)
			add_front_select_list(&alst, new, file->d_name);
	}
	free_double_tab(tabz);
	closedir(rep);
}
