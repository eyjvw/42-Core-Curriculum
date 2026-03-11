/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:05:52 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/20 04:13:15 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_pipex
{
	int		pipe_fd[2];
	int		infile;
	int		outfile;
	int		prev_fd;
	int		here_doc;
	int		cmds_count;
	char	*limiter;

	int		ac;
	char	**av;
	char	**env;
}	t_pipex;

#endif
