/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 02:57:36 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/20 06:25:44 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

static void	ft_child_process(t_pipex *px, int i)
{
	close(px->pipe_fd[0]);
	if (i == 0)
		dup2(px->infile, STDIN_FILENO);
	else
		(dup2(px->prev_fd, STDIN_FILENO), close(px->prev_fd));
	if (i < px->cmds_count - 1)
		dup2(px->pipe_fd[1], STDOUT_FILENO);
	else
		dup2(px->outfile, STDOUT_FILENO);
	close(px->pipe_fd[1]);
	ft_exec(px, px->av[2 + px->here_doc + i]);
}

void	ft_pipex(t_pipex *px)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < px->cmds_count)
	{
		if (pipe(px->pipe_fd) == -1)
			(ft_close(px), ft_putstr_fd(2, "pipe error\n"), exit(1));
		pid = fork();
		if (pid == -1)
			(ft_close(px), ft_putstr_fd(2, "fork error\n"), exit(1));
		if (pid == 0)
			ft_child_process(px, i);
		close(px->pipe_fd[1]);
		if (i > 0)
			close(px->prev_fd);
		px->prev_fd = px->pipe_fd[0];
		i++;
	}
	close(px->prev_fd);
	while (wait(NULL) > 0)
		;
}

int	main(int ac, char **av, char **env)
{
	t_pipex	px;

	if (ac < 5)
		return (ft_putstr_fd(2, ARG_ERROR), 1);
	ft_init(&px, ac, av, env);
	ft_open(&px);
	if (px.here_doc)
	{
		ft_here_doc(&px);
		px.infile = px.pipe_fd[0];
	}
	ft_pipex(&px);
	ft_close(&px);
	return (0);
}
