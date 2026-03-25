/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:51:45 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 20:51:53 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void	ui(t_game *game, t_display *display)
{
	render_crossair(game);
	img_to_frame(&display->frame, &display->minimap,
		get_point(
			display->minimap.width,
			display->minimap.height),
		get_point(0, 0));
	img_to_frame(&display->frame,
		&display->gun.frames[display->gun.current_frame],
		get_point(
			display->gun.frames[display->gun.current_frame].width,
			display->gun.frames[display->gun.current_frame].height),
		get_point(
			RES_X - display->gun.frames[display->gun.current_frame].width,
			RES_Y - display->gun.frames[display->gun.current_frame].height
			- 65));
}
