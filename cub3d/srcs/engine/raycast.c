/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:38:26 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/22 14:02:34 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	put_frame(t_game *game, t_ray ray)
{
	init_ray(&ray, &game->dda);
	vertical_draw(game, ray);
}

void	init_ray(t_ray *ray, t_ddata *dda)
{
	ray->line_len = (int)(RES_Y / dda->wall_dist);
	ray->line_start = -ray->line_len / 2 + RES_Y / 2;
	ray->line_end = ray->line_len / 2 + RES_Y / 2;
	if (ray->line_start < 0)
		ray->line_start = 0;
	if (ray->line_end >= RES_Y)
		ray->line_end = RES_Y - 1;
}

void	raycast(t_game *game)
{
	int		i;
	t_ray	ray;
	float	offset;

	i = -1;
	offset = 0;
	ft_bzero(&ray, sizeof(t_ray));
	draw_ceil(&game->display.frame, rgb_to_hex(game->data.colors[CEIL]));
	draw_floor(&game->display.frame, rgb_to_hex(game->data.colors[FLOOR]));
	while (++i < RES_X)
	{
		ray.id = i;
		offset = (float)(((2.0 * i) / RES_X) - 1);
		ray.dir.x = game->player.dir.x + game->player.cplane.x * offset;
		ray.dir.y = game->player.dir.y + game->player.cplane.y * offset;
		game->dda = dda(game->player.pos, game->data.map, &ray);
		put_frame(game, ray);
		draw_line(&game->display.minimap, normalize_tidle(game->player.pos,
				game->display.map_tidle_size),
			normalize_tidle(game->dda.hit_pos, game->display.map_tidle_size),
			ORANGE);
	}
	door_cast(game);
}
