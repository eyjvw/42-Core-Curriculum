/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:13:54 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/20 06:19:21 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_read_heredoc(t_pipex *px)
{
	char	*line;
	size_t	len_line;

	close(px->pipe_fd[0]);
	while (1)
	{
		ft_putstr_fd(1, "heredoc> ");
		line = get_next_line(0);
		if (!line)
			exit(0);
		len_line = ft_strlen(line);
		if (len_line > 0 && line[len_line - 1] == '\n')
			line[len_line - 1] = '\0';
		if (ft_strcmp(line, px->limiter) == 0)
			(free(line), exit(0));
		write(px->pipe_fd[1], line, ft_strlen(line));
		write(px->pipe_fd[1], "\n", 1);
		free(line);
	}
}

void	ft_here_doc(t_pipex *px)
{
	pid_t	reader;

	if (pipe(px->pipe_fd) == -1)
		return (ft_close(px), ft_putstr_fd(2, "Pipe error\n"));
	reader = fork();
	if (reader == -1)
		return (ft_close(px), ft_putstr_fd(2, "Fork error\n"));
	if (reader == 0)
		ft_read_heredoc(px);
	else
	{
		close(px->pipe_fd[1]);
		wait(NULL);
	}
}
