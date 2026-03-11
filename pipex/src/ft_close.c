/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:32:28 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 05:34:14 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_close(t_pipex *px)
{
	if (px->infile != -1)
		close(px->infile);
	if (px->outfile != -1)
		close(px->outfile);
}
