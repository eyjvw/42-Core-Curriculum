/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 04:07:22 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:37:52 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	init_dda(t_ddata *dda, t_point player, t_point dir)
{
	dda->delta = get_delta(dir);
	dda->map.x = (int)player.x;
	dda->map.y = (int)player.y;
	dda->step.x = 1;
	dda->step.y = 1;
	dda->side_dist.y = (dda->map.y + 1.0 - player.y) * dda->delta.y;
	dda->side_dist.x = (dda->map.x + 1.0 - player.x) * dda->delta.x;
	if (dir.x < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (player.x - dda->map.x) * dda->delta.x;
	}
	if (dir.y < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (player.y - dda->map.y) * dda->delta.y;
	}
}

static void	update_dda(t_ddata *dda, char mod)
{
	if (mod == 'X')
	{
		dda->side_dist.x += dda->delta.x;
		dda->map.x += dda->step.x;
		dda->side = false;
	}
	if (mod == 'Y')
	{
		dda->side_dist.y += dda->delta.y;
		dda->map.y += dda->step.y;
		dda->side = true;
	}
}

t_ddata	dda(t_point player, char **map, t_ray *ray)
{
	t_ddata	dda;

	ft_bzero(&dda, sizeof(dda));
	init_dda(&dda, player, ray->dir);
	while (map[dda.map.y][dda.map.x] != '1'
		&& map[dda.map.y][dda.map.x] != 'D'
		&& map[dda.map.y][dda.map.x] != 'O')
	{
		if (dda.side_dist.x < dda.side_dist.y)
			update_dda(&dda, 'X');
		else
			update_dda(&dda, 'Y');
	}
	dda.wall_dist = get_walldist(&dda, player, ray->dir);
	dda.hit_pos.x = player.x + ray->dir.x * dda.wall_dist;
	dda.hit_pos.y = player.y + ray->dir.y * dda.wall_dist;
	dda.wall_x = get_wallx(&dda, ray->dir, player);
	dda.wall_x -= floor(dda.wall_x);
	return (dda);
}
