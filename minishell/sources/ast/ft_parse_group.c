/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_group.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 01:15:11 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 01:20:30 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*ft_parse_group(t_tokens **tokens)
{
	t_ast	*ast;

	if (!*tokens)
		return (NULL);
	if ((*tokens)->type == LPAREN)
	{
		*tokens = (*tokens)->next;
		ast = ft_create_ast(AST_SUBSHELL);
		if (!ast)
			return (NULL);
		ast->left = ft_parse_pipe(tokens);
		if (*tokens && (*tokens)->type == RPAREN)
			*tokens = (*tokens)->next;
		return (ft_parse_redir(tokens, ast));
	}
	ast = ft_parse_command(tokens);
	return (ft_parse_redir(tokens, ast));
}
