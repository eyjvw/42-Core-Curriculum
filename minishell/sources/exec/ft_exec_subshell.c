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
	int		status;

	pid = fork();
	if (pid == 0)
		exit(ft_exec_node(shell, node->left));
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
