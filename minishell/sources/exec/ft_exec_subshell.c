/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:09:39 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 18:09:58 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_subshell(t_shell *shell, t_ast *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), 1);
	if (pid == 0)
	{
		ft_reset();
		shell->interactive = false;
		ft_exit_child(shell, ft_exec_node(shell, node->left));
	}
	return (ft_wait(shell, pid));
}
