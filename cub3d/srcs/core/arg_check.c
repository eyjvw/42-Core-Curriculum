/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:03:07 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:37:32 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	check_path(char *path)
{
	int		fd;
	size_t	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(&path[len - 4], ".cub"))
		ft_exit(INVALID_FORMAT);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(INVALID_PATH);
	close(fd);
}

void	check_args(int ac, char **av)
{
	if (ac < 2)
		ft_exit(TOO_LITT_ARGS);
	if (ac > 2)
		ft_exit(TOO_MANY_ARGS);
	if (RES_X != 1920 || RES_Y != 1080)
		ft_exit(INVALID_RES);
	check_path(av[1]);
}
