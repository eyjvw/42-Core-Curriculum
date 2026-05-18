/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 03:03:21 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 04:24:37 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_and(t_shell *shell, t_ast *node)
{
	shell->exit_code = ft_exec_node(shell, node->left);
	if (shell->exit_code == 0)
		return (ft_exec_node(shell, node->right));
	return (shell->exit_code);
}
