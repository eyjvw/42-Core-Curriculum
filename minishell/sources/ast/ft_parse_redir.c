/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 01:19:10 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 04:25:11 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*ft_parse_redir(t_tokens **tokens, t_ast *cmd)
{
	t_ast	*node;

	if (!*tokens || !ft_is_red((*tokens)->type))
		return (cmd);
	node = ft_create_ast(AST_REDIR);
	if (!node)
		return (cmd);
	node->redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == WORD)
	{
		node->file = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	node->left = cmd;
	return (ft_parse_redir(tokens, node));
}
