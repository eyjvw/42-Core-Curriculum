/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:09:28 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 21:11:45 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

bool	hit_door(t_game *game, t_ddata dda)
{
	return (is_door(game->data.map, dda.map.x, dda.map.y));
}

bool	is_door(char **map, int x, int y)
{
	return (map[y][x] == 'D');
}

void	update_door(t_game *game)
{
	t_ipoint	door;

	door.x = (int)(game->player.pos.x + game->player.dir.x * 1.3);
	door.y = (int)(game->player.pos.y + game->player.dir.y * 1.3);
	if (is_door(game->data.map, door.x, door.y)
		|| game->data.map[door.y][door.x] == 'd')
	{
		if (game->data.map[door.y][door.x] == 'D')
			game->data.map[door.y][door.x] = 'd';
		else
			game->data.map[door.y][door.x] = 'D';
	}
	game->keys[KF_ID] = false;
}

void	door_cast(t_game *game)
{
	t_ray	ray;
	double	offset;

	offset = (float)(((2.0 * (RES_X / 2)) / RES_X) - 1);
	ray.dir.x = game->player.dir.x + game->player.cplane.x * offset;
	ray.dir.y = game->player.dir.y + game->player.cplane.y * offset;
	game->ddoor = dda(game->player.pos, game->data.map, &ray);
}
