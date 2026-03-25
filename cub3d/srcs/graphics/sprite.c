/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:39:34 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:38:11 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static char	*get_path(int i, const char *s_path)
{
	char	*num;
	char	*path;
	char	*f_path;

	num = ft_itoa(i);
	path = ft_strjoin(s_path, num);
	f_path = ft_strjoin(path, ".xpm");
	free(path);
	free(num);
	return (f_path);
}

bool	init_sprite(t_display *display, t_sprite *sprite,
		const char *s_path, int frame_amount)
{
	int		i;
	char	*path;

	i = -1;
	ft_bzero(sprite, sizeof(t_sprite));
	sprite->frame_amount = frame_amount;
	sprite->frames = malloc(sizeof(t_img) * frame_amount);
	while (++i < frame_amount)
	{
		path = get_path(i, s_path);
		sprite->frames[i].img = mlx_xpm_file_to_image(display->main, path,
				&sprite->frames[i].width,
				&sprite->frames[i].height);
		if (!sprite->frames[i].img)
			return (false);
		sprite->frames[i].addr = mlx_get_data_addr(sprite->frames[i].img,
				&sprite->frames[i].bits_per_pixel,
				&sprite->frames[i].line_length,
				&sprite->frames[i].endian);
		if (!sprite->frames[i].addr)
			return (false);
		free(path);
	}
	return (true);
}

void	destroy_sprite(t_display *display, t_sprite *sprite)
{
	int	i;

	i = 0;
	while (i < sprite->frame_amount)
	{
		if (sprite->frames[i].img)
			mlx_destroy_image(display->main, sprite->frames[i].img);
		i++;
	}
	if (sprite->frames)
		free(sprite->frames);
}
