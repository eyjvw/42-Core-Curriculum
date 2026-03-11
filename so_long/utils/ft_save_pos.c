/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 07:29:23 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/04 03:21:39 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_save_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->map->width = ft_strlen(game->map->map[0]);
	game->map->height = ft_arrlen((const char **)game->map->map);
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->map[y][x] == 'E')
			{
				game->map->exit_x = x;
				game->map->exit_y = y;
			}
			if (game->map->map[y][x] == 'P')
			{
				game->map->player_x = x;
				game->map->player_y = y;
			}
			x++;
		}
		y++;
	}
}
