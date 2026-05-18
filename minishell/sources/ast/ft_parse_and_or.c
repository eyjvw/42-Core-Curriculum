/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_and_or.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 01:12:29 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 04:25:23 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*ft_parse_and_or(t_tokens **tokens)
{
	t_ast		*left;
	t_ast		*ast;
	t_ast_type	type;

	left = ft_parse_pipe(tokens);
	if (!*tokens || ((*tokens)->type != AND_IF && (*tokens)->type != OR_IF))
		return (left);
	if ((*tokens)->type == AND_IF)
		type = AST_AND;
	else
		type = AST_OR;
	ast = ft_create_ast(type);
	if (!ast)
		return (left);
	*tokens = (*tokens)->next;
	ast->left = left;
	ast->right = ft_parse_and_or(tokens);
	return (ast);
}
