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

static int	ft_read_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (130);
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

static int	ft_handle_heredoc(t_shell *shell, t_ast *node, int fd)
{
	int	saved;
	int	ret;

	if (!node->left)
	{
		close(fd);
		return (0);
	}
	saved = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	ret = ft_exec_node(shell, node->left);
	dup2(saved, STDIN_FILENO);
	close(saved);
	return (ret);
}

int	ft_exec_heredoc(t_shell *shell, t_ast *node)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	int		ret;

	if (!node->file)
		return (1);
	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		ret = ft_read_heredoc(fd[1], node->file);
		close(fd[1]);
		ft_final_clean(shell);
		exit(ret);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	ft_sigint(PROMPT);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (close(fd[0]), SIGNAL_INTERUP);
	return (ft_handle_heredoc(shell, node, fd[0]));
}
