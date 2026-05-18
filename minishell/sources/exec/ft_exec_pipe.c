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
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exit(ft_exec_node(shell, node->left));
}

static void	ft_exec_right(t_shell *shell, t_ast *node, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exit(ft_exec_node(shell, node->right));
}

int	ft_exec_pipe(t_shell *shell, t_ast *node)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (node->right && node->right->type == AST_REDIR
		&& node->right->redir_type == HERE_DOC)
	{
		if (ft_exec_heredoc(shell, node->right) != 0)
			return (1);
	}
	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	pid_left = fork();
	if (pid_left == 0)
		ft_exec_left(shell, node, fd);
	pid_right = fork();
	if (pid_right == 0)
		ft_exec_right(shell, node, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	return (WEXITSTATUS(status));
}
