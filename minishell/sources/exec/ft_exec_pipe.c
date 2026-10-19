/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:45:28 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 01:25:07 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_exec_left(t_shell *shell, t_ast *node, int *fd)
{
	ft_reset();
	shell->interactive = false;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_exit_child(shell, ft_exec_node(shell, node->left));
}

static void	ft_exec_right(t_shell *shell, t_ast *node, int *fd)
{
	ft_reset();
	shell->interactive = false;
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_exit_child(shell, ft_exec_node(shell, node->right));
}

static int	ft_wait_pipe(t_shell *shell, pid_t pid_left, pid_t pid_right)
{
	int	status;
	int	ret;

	status = 0;
	if (pid_left > 0)
		waitpid(pid_left, &status, 0);
	if (pid_right < 0)
		return (1);
	ret = ft_wait(shell, pid_right);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT
		&& ret != EXIT_COMMAND_FAILED + SIGINT && shell->interactive)
		ft_putstr_fd(STDERR_FILENO, "\n");
	return (ret);
}

int	ft_exec_pipe(t_shell *shell, t_ast *node)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fd) < 0)
		return (perror("minishell: pipe"), 1);
	pid_left = fork();
	if (pid_left == 0)
		ft_exec_left(shell, node, fd);
	pid_right = -1;
	if (pid_left > 0)
		pid_right = fork();
	if (pid_right == 0)
		ft_exec_right(shell, node, fd);
	if (pid_right < 0)
		perror("minishell: fork");
	close(fd[0]);
	close(fd[1]);
	return (ft_wait_pipe(shell, pid_left, pid_right));
}
