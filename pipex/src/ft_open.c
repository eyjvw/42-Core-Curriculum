/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:29:16 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 05:40:20 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

void	ft_open(t_pipex *px)
{
	if (!px->here_doc)
	{
		px->infile = open(px->av[1], O_RDONLY);
		if (px->infile == -1)
		{
			ft_putstr_fd(2, px->av[1]);
			ft_putstr_fd(2, ": ");
			ft_putstr_fd(2, "No such file or directory or permission denied\n");
			exit(1);
		}
	}
	if (px->here_doc)
		px->outfile = open(px->av[px->ac - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		px->outfile = open(px->av[px->ac - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->outfile == -1)
	{
		if (px->infile != -1)
			close(px->infile);
		(ft_putstr_fd(2, px->av[px->ac - 1]), ft_putstr_fd(2, ": "));
		ft_putstr_fd(2, "Permission denied or cannot create file\n");
		exit(1);
	}
}
