/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:39:53 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 20:41:08 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	my_mlx_pixel_put(t_img *data, t_point px, int color)
{
	char	*dst;

	dst = data->addr + ((int)px.y * data->line_length
			+ (int)px.x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_img *img, t_point start, t_point end, int color)
{
	t_point	delta;
	t_point	pixel;
	double	pixels;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	pixels = fabs(delta.y);
	if (fabs(delta.x) > fabs(delta.y))
		pixels = fabs(delta.x);
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = start.x;
	pixel.y = start.y;
	while (pixels > 0)
	{
		my_mlx_pixel_put(img, pixel, color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		pixels--;
	}
}

void	draw_square(t_img *img, t_point start, int size, int color)
{
	t_point	px;

	px.x = start.x;
	px.y = start.y;
	while ((px.y - start.y) < size)
	{
		while ((px.x - start.x) < size)
		{
			my_mlx_pixel_put(img, px, color);
			px.x++;
		}
		px.x = start.x;
		px.y++;
	}
}

void	draw_rectangle(t_img *img, t_point pos, int len, int hei)
{
	t_ipoint	coo;

	coo.x = pos.x;
	coo.y = pos.y;
	while ((coo.y - pos.y) < hei)
	{
		while ((coo.x - pos.x) < len)
		{
			my_mlx_pixel_put(img, get_point(coo.x, coo.y), WHITE);
			coo.x++;
		}
		coo.x = pos.x;
		coo.y++;
	}
}
