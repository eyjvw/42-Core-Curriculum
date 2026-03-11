/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:05:52 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 09:08:22 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef struct s_pipex
{
	int		pipe_fd[2];
	int		infile;
	int		outfile;
	int		prev_fd;
	int		here_doc;
	int		cmds_count;
	int		ac;

	char	*limiter;

	char	**av;
	char	**env;
}	t_pipex;
