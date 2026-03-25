/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:35:14 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 21:20:58 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H
# include "structs.h"
# include "engine.h"

//Crosshair
# define CROSSHAIR_LINE_THICK	1
# define CROSSHAIR_LINE_LEN		4
# define CENTER_OFFSET			2

//Minimap
# define MINIMAP_SIZE			350

//Gun sprite
# define GUN_FRAME_AMOUNT		10
# define SPRITE_GUN_PATH		"./assets/sprites/gun/"

# define WHITE					0xFFFFFF
# define ORANGE					0xFFA500
# define GREY					0x808080
# define RED					0xFF0000
# define BLUE					0x0000FF
# define PINK					0xFD6C9E

void		ui(t_game *game, t_display *display);

//Crosshair
void		render_crossair(t_game *game);

//Minimap
t_point		normalize_tidle(t_point px, int tidle_size);
t_point		normalize_player(t_point px, int tidle_size);
void		draw_map(t_display *display, char **map);
void		img_to_frame(t_img *frame, t_img *img, t_point	h_and_w,
				t_point place);

#endif
