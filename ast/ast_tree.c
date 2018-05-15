/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 09:24:56 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:59:18 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

t_btree			*new_tree(t_token *token)
{
	t_btree *ast;

	if (!(token))
		return (NULL);
	if (!(ast = malloc(sizeof(t_btree))))
		return (NULL);
	ast->data = token;
	ast->left = NULL;
	ast->right = NULL;
	ast->parent = NULL;
	return (ast);
}

t_btree			*join_tree(t_btree *left, t_btree *right, t_token *token)
{
	t_btree *ast;

	if (!(ast = new_tree(token)))
		return (NULL);
	ast->left = left;
	ast->right = right;
	if (left != NULL)
		left->parent = ast;
	if (right != NULL)
		right->parent = ast;
	return (ast);
}

void			clean_tree(t_btree *ast)
{
	t_token *tmp;
	t_token *tmp2;

	if (ast == NULL)
		return ;
	tmp = ast->data;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->str)
			free(tmp->str);
		if (tmp->filename)
			free(tmp->filename);
		free(tmp);
		tmp = tmp2;
	}
	clean_tree(ast->left);
	clean_tree(ast->right);
	free(ast);
}
