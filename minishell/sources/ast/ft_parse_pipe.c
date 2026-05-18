/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 01:14:03 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 01:21:27 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast	*ft_parse_simple_command(t_tokens **tokens)
{
	return (ft_parse_group(tokens));
}

t_ast	*ft_parse_pipe(t_tokens **tokens)
{
	t_ast	*left;
	t_ast	*ast;

	left = ft_parse_simple_command(tokens);
	if (!*tokens || (*tokens)->type != PIPE)
		return (left);
	ast = ft_create_ast(AST_PIPE);
	if (!ast)
		return (left);
	*tokens = (*tokens)->next;
	ast->left = left;
	ast->right = ft_parse_pipe(tokens);
	return (ast);
}
