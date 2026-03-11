/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:06:16 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 05:34:14 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_init(t_pipex *px, int ac, char **av, char **env)
{
	px->here_doc = 0;
	px->limiter = NULL;
	px->infile = -1;
	px->outfile = -1;
	px->prev_fd = -1;
	px->ac = ac;
	px->av = av;
	px->env = env;
	if (ac > 2 && ft_strcmp(av[1], "here_doc") == 0)
	{
		px->here_doc = 1;
		px->limiter = av[2];
	}
	px->cmds_count = px->ac - 3 - px->here_doc;
}
