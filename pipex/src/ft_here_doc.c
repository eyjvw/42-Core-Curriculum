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
		write(px->infile, line, ft_strlen(line));
		write(px->infile, "\n", 1);
		free(line);
	}
}

void	ft_here_doc(t_pipex *px)
{
	pid_t	reader;

	unlink(HEREDOC_TMP);
	px->infile = open(HEREDOC_TMP, O_WRONLY | O_CREAT | O_EXCL, 0600);
	if (px->infile == -1)
		(perror(HEREDOC_TMP), ft_close(px), exit(1));
	reader = fork();
	if (reader == -1)
		(unlink(HEREDOC_TMP), ft_close(px), ft_putstr_fd(2, "Fork error\n"),
			exit(1));
	if (reader == 0)
		ft_read_heredoc(px);
	waitpid(reader, NULL, 0);
	close(px->infile);
	px->infile = open(HEREDOC_TMP, O_RDONLY);
	unlink(HEREDOC_TMP);
	if (px->infile == -1)
		(perror(HEREDOC_TMP), ft_close(px), exit(1));
}
