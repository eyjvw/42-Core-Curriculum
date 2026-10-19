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

static int	ft_heredoc_pipe(t_shell *shell, char *body, pid_t *writer)
{
	int	fd[2];

	if (pipe(fd) < 0)
		return (perror("minishell: pipe"), -1);
	*writer = fork();
	if (*writer == 0)
	{
		ft_reset();
		close(fd[0]);
		ft_close_fds(shell->ast);
		ft_putstr_fd(fd[1], body);
		close(fd[1]);
		ft_exit_child(shell, 0);
	}
	close(fd[1]);
	if (*writer < 0)
		return (perror("minishell: fork"), close(fd[0]), -1);
	return (fd[0]);
}

static int	ft_open_redir(t_shell *shell, t_ast *node, pid_t *writer)
{
	char	*file;
	int		fd;

	if (node->redir_type == HERE_DOC)
		return (ft_heredoc_pipe(shell, node->file, writer));
	file = ft_expand_file(shell, node->file);
	if (!file)
		return (-1);
	if (node->redir_type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->redir_type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(file, NULL, strerror(errno));
	free(file);
	return (fd);
}

int	ft_exec_redir(t_shell *shell, t_ast *node)
{
	int		fd;
	int		target;
	int		ret;
	pid_t	writer;

	writer = -1;
	fd = ft_open_redir(shell, node, &writer);
	if (fd < 0)
		return (1);
	target = STDOUT_FILENO;
	if (node->redir_type == REDIR_IN || node->redir_type == HERE_DOC)
		target = STDIN_FILENO;
	node->fd = dup(target);
	dup2(fd, target);
	close(fd);
	ret = ft_exec_node(shell, node->left);
	dup2(node->fd, target);
	close(node->fd);
	node->fd = -1;
	if (writer > 0)
		waitpid(writer, NULL, 0);
	return (ret);
}
