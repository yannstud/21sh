/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalaun <ysalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:43:03 by amottier          #+#    #+#             */
/*   Updated: 2018/04/16 11:59:21 by ysalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vingtetunsh.h"

t_btree			*split_cmd(t_token *head)
{
	t_token *node;

	node = head;
	if (node)
		while (node->next)
			node = node->next;
	if ((node = has_operator(node)))
		return (ast_operator(node));
	if ((node = has_redirection(head)))
		return (ast_redirection(node, head));
	return (new_tree(head));
}

void			gen_tree_prefix(t_btree *ast)
{
	t_btree *tmp;

	if (ast == NULL)
		return ;
	if (ast->parent != NULL)
	{
		tmp = split_cmd(ast->data);
		if (tmp)
		{
			ast->left = tmp->left;
			ast->right = tmp->right;
			if (ast->left)
				tmp->left->parent = ast;
			if (ast->right)
				tmp->right->parent = ast;
			ast->data = tmp->data;
			free(tmp);
		}
	}
	if (ast && ast->left != NULL)
		gen_tree_prefix(ast->left);
	if (ast && ast->right != NULL)
		gen_tree_prefix(ast->right);
}

t_btree			*create_ast(t_token *head)
{
	t_btree *ast;
	t_token *tmp;

	tmp = head;
	if ((ast = split_cmd(tmp)))
		gen_tree_prefix(ast);
	else
		ft_putstr("Error AST\n");
	return (ast);
}
