/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:52:11 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 04:00:24 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_node(t_shell *shell, t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == AST_CMD)
		return (ft_exec_cmd(shell, node));
	if (node->type == AST_PIPE)
		return (ft_exec_pipe(shell, node));
	if (node->type == AST_REDIR)
		return (ft_exec_redir(shell, node));
	if (node->type == AST_AND)
		return (ft_exec_and(shell, node));
	if (node->type == AST_OR)
		return (ft_exec_or(shell, node));
	if (node->type == AST_SUBSHELL)
		return (ft_exec_subshell(shell, node));
	return (0);
}
