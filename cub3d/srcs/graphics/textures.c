/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:10:35 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 21:30:59 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_ceil(t_img *frame, int color)
{
	int	y;

	y = -1;
	while (++y < (RES_Y / 2))
		draw_line(frame, get_point(0, y),
			get_point(frame->line_length, y), color);
}

void	draw_floor(t_img *frame, int color)
{
	int	x;

	x = RES_Y / 2;
	while (++x < (RES_Y))
		draw_line(frame, get_point(0, x),
			get_point(frame->line_length, x), color);
}

static t_img	*get_texture(t_ddata dda, t_game *game)
{
	if (hit_door(game, dda))
		return (&game->display.texture[DOOR]);
	if (dda.side == true)
	{
		if (dda.step.y < 0)
			return (&game->display.texture[EAST]);
		return (&game->display.texture[WEST]);
	}
	if (dda.step.x < 0)
		return (&game->display.texture[NORTH]);
	return (&game->display.texture[SOUTH]);
}

void	vertical_draw(t_game *game, t_ray ray)
{
	int		y;
	t_tex	tex;

	y = ray.line_start - 1;
	tex.img = get_texture(game->dda, game);
	tex.coo.x = (int)(game->dda.wall_x
			* (double)(tex.img->width));
	if (!game->dda.side && ray.dir.x < 0)
		tex.coo.x = tex.img->width - tex.coo.x - 1;
	if (game->dda.side && ray.dir.y > 0)
		tex.coo.x = tex.img->width - tex.coo.x - 1;
	tex.step = (double)tex.img->height
		/ (double)ray.line_len;
	tex.pos = (double)(ray.line_start - RES_Y / 2 + ray.line_len / 2) *tex.step;
	while (++y < ray.line_end)
	{
		tex.coo.y = (int)tex.pos;
		tex.pos += tex.step;
		tex.color = *(int *)(tex.img->addr
				+ tex.coo.y * tex.img->line_length
				+ tex.coo.x * 4);
		if ((tex.color & 0xFF000000) == 0)
			my_mlx_pixel_put(&game->display.frame,
				get_point(ray.id, y), tex.color);
	}
}
