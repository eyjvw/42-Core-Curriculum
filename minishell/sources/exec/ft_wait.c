/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_wait(t_shell *shell, pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFSIGNALED(status))
	{
		if (shell->interactive && WTERMSIG(status) == SIGINT)
			ft_putstr_fd(STDERR_FILENO, "\n");
		else if (shell->interactive && WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd(STDERR_FILENO, "Quit (core dumped)\n");
		return (EXIT_COMMAND_FAILED + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
