/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:47:02 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 04:42:13 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_open_redir(t_ast *node)
{
	if (node->redir_type == REDIR_OUT)
		return (open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (node->redir_type == APPEND)
		return (open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (node->redir_type == REDIR_IN)
		return (open(node->file, O_RDONLY));
	return (-1);
}

static void	ft_restore_fd(t_ast *node, int saved_fd)
{
	if (node->redir_type == REDIR_IN)
		dup2(saved_fd, STDIN_FILENO);
	else
		dup2(saved_fd, STDOUT_FILENO);
	close(saved_fd);
}

int	ft_exec_redir(t_shell *shell, t_ast *node)
{
	int	fd;
	int	saved_fd;
	int	ret;

	if (node->redir_type == HERE_DOC)
		return (ft_exec_heredoc(shell, node));
	fd = ft_open_redir(node);
	if (fd < 0)
		return (perror(node->file), 1);
	if (node->redir_type == REDIR_IN)
		saved_fd = dup(STDIN_FILENO);
	else
		saved_fd = dup(STDOUT_FILENO);
	if (node->redir_type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	ret = ft_exec_node(shell, node->left);
	ft_restore_fd(node, saved_fd);
	return (ret);
}
