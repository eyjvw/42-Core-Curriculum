/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:18:06 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:48:15 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "io.h"
# include "structs.h"

//Doors
void	update_door(t_game *game);
void	door_cast(t_game *game);
bool	hit_door(t_game *game, t_ddata dda);

//Sprites
bool	init_sprite(t_display *display, t_sprite *sprite,
			const char *s_path, int frame_amount);
void	destroy_sprite(t_display *display, t_sprite *sprite);
void	update_gun(t_game *game, t_sprite *gun);

//Animations
void	update_gun(t_game *game, t_sprite *gun);

//Textures
void	draw_floor(t_img *frame, int color);
void	draw_ceil(t_img *frame, int color);

#endif
