/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 01:27:29 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 02:30:10 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_heredoc_eof(char *delimiter)
{
	char	*msg;

	msg = ft_strjoin(HEREDOC_LIMITED, delimiter);
	msg = ft_strjoin_and_free(msg, "')");
	ft_error("warning", NULL, msg);
	free(msg);
}

static void	ft_read_heredoc(t_shell *shell, int fd, char *delimiter,
	bool expand)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = ft_get_line(shell, "> ");
		if (!line)
			ft_heredoc_eof(delimiter);
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		if (expand)
		{
			tmp = ft_expand_variables(shell, line, false);
			free(line);
			line = tmp;
		}
		ft_putstr_fd(fd, line);
		ft_putstr_fd(fd, "\n");
		free(line);
	}
	free(line);
}

static void	ft_heredoc_child(t_shell *shell, t_ast *node, int *fd)
{
	char	*delimiter;
	bool	expand;

	ft_sigint(STATE_HERE_DOC);
	close(fd[0]);
	expand = (!ft_strchr(node->file, '\'') && !ft_strchr(node->file, '"'));
	delimiter = ft_remove_quotes(node->file);
	if (delimiter)
		ft_read_heredoc(shell, fd[1], delimiter, expand);
	free(delimiter);
	close(fd[1]);
	ft_exit_child(shell, 0);
}

static int	ft_heredoc(t_shell *shell, t_ast *node)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	char	*body;

	if (pipe(fd) < 0)
		return (perror("minishell: pipe"), 1);
	pid = fork();
	if (pid == 0)
		ft_heredoc_child(shell, node, fd);
	close(fd[1]);
	body = NULL;
	if (pid > 0)
		body = ft_read_all(fd[0]);
	close(fd[0]);
	if (pid < 0 || waitpid(pid, &status, 0) < 0 || !body)
		return (free(body), perror("minishell: heredoc"), 1);
	if (WIFSIGNALED(status))
		return (free(body), ft_putstr_fd(STDOUT_FILENO, "\n"), SIGNAL_INTERUP);
	free(node->file);
	node->file = body;
	return (0);
}

int	ft_heredocs(t_shell *shell, t_ast *node)
{
	t_ast	*bottom;
	int		ret;

	if (!node)
		return (0);
	if (node->type != AST_REDIR)
	{
		ret = ft_heredocs(shell, node->left);
		if (!ret)
			ret = ft_heredocs(shell, node->right);
		return (ret);
	}
	bottom = node;
	while (bottom && bottom->type == AST_REDIR)
		bottom = bottom->left;
	ret = ft_heredocs(shell, bottom);
	while (!ret && node && node->type == AST_REDIR)
	{
		if (node->redir_type == HERE_DOC)
			ret = ft_heredoc(shell, node);
		node = node->left;
	}
	return (ret);
}
