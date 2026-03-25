/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:42:57 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 21:19:45 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static bool	init_minimap(t_display *display, t_data *data)
{
	display->map_tidle_size = MINIMAP_SIZE / ft_strmaxlen(data->map);
	display->minimap.height = ft_doublelen(data->map)
		* (display->map_tidle_size + 2);
	display->minimap.width = (ft_strmaxlen(data->map) - 1)
		* (display->map_tidle_size + 2);
	display->minimap.img = mlx_new_image(display->main,
			display->minimap.width,
			display->minimap.height);
	if (!display->minimap.img)
		return (false);
	display->minimap.addr = mlx_get_data_addr(display->minimap.img,
			&display->minimap.bits_per_pixel,
			&display->minimap.line_length,
			&display->minimap.endian);
	if (!display->minimap.addr)
		return (false);
	return (true);
}

static bool	init_textures(t_display *display, t_data *data)
{
	int	i;

	i = -1;
	while (++i < TEXTURE_AMOUNT)
	{
		display->texture[i].img = mlx_xpm_file_to_image(display->main,
				data->texture_path[i],
				&display->texture[i].width,
				&display->texture[i].height);
		if (!display->texture[i].img)
			return (false);
		display->texture[i].addr = mlx_get_data_addr(display->texture[i].img,
				&display->texture[i].bits_per_pixel,
				&display->texture[i].line_length,
				&display->texture[i].endian);
		if (!display->texture[i].addr)
			return (false);
	}
	return (true);
}

bool	init_display(t_display *display, t_data *data)
{
	display->main = mlx_init();
	if (!display->main)
		return (false);
	display->window = mlx_new_window(display->main, RES_X, RES_Y, "cub3d");
	if (!display->window)
		return (false);
	display->frame.img = mlx_new_image(display->main, RES_X, RES_Y);
	if (!display->frame.img)
		return (false);
	display->frame.addr = mlx_get_data_addr(display->frame.img,
			&display->frame.bits_per_pixel,
			&display->frame.line_length,
			&display->frame.endian);
	if (!display->frame.addr)
		return (false);
	if (!init_minimap(display, data) || !init_textures(display, data)
		|| !init_sprite(display, &display->gun,
			SPRITE_GUN_PATH, GUN_FRAME_AMOUNT))
		return (false);
	return (true);
}

void	kill_display(t_display *display)
{
	int	i;

	i = -1;
	destroy_sprite(display, &display->gun);
	if (display->frame.img)
		mlx_destroy_image(display->main, display->frame.img);
	if (display->minimap.img)
		mlx_destroy_image(display->main, display->minimap.img);
	while (++i < TEXTURE_AMOUNT)
	{
		if (display->texture[i].img)
			mlx_destroy_image(display->main, display->texture[i].img);
	}
	if (display->window)
		mlx_destroy_window(display->main, display->window);
	if (display->main)
		mlx_destroy_display(display->main);
	free(display->main);
}
