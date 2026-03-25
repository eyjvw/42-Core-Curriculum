/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:58:39 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/22 14:01:10 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "others.h"

static	void	write_usage(void)
{
	ft_write_error("Usage : ./cub3d <map.cub>\n");
}

void	write_error(uint8_t error)
{
	ft_write_error("cub3d: ");
	if (error == TOO_MANY_ARGS)
		(ft_write_error("Too Many Arguments\n"), write_usage());
	else if (error == TOO_LITT_ARGS)
		(ft_write_error("Not Enough Arguments\n"), write_usage());
	else if (error == INVALID_FORMAT)
		ft_write_error("Invalid Format, Map must be .cub\n");
	else if (error == INVALID_PATH)
		ft_write_error("File does not exist or Missing Permissions\n");
	else if (error == INVALID_RES)
		ft_write_error("Supported resolutions : 1920x1080\n");
}

void	ft_exit(ssize_t	error)
{
	if (error >= 0)
		(write_error(error), exit(EXIT_FAILURE));
	exit(EXIT_SUCCESS);
}
