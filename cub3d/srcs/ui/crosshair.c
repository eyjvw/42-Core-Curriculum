/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:57:17 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 18:29:45 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void	render_crossair(t_game *game)
{
	draw_rectangle(&game->display.frame, get_point((RES_X / 2)
			- CROSSHAIR_LINE_LEN - CENTER_OFFSET, (RES_Y / 2)),
		CROSSHAIR_LINE_LEN, CROSSHAIR_LINE_THICK);
	draw_rectangle(&game->display.frame, get_point((RES_X / 2)
			+ CROSSHAIR_LINE_THICK + CENTER_OFFSET, (RES_Y / 2)),
		CROSSHAIR_LINE_LEN, CROSSHAIR_LINE_THICK);
	draw_rectangle(&game->display.frame, get_point((RES_X / 2),
			(RES_Y / 2) - CROSSHAIR_LINE_LEN - CENTER_OFFSET),
		CROSSHAIR_LINE_THICK, CROSSHAIR_LINE_LEN);
	draw_rectangle(&game->display.frame, get_point((RES_X / 2),
			(RES_Y / 2) + CROSSHAIR_LINE_THICK + CENTER_OFFSET),
		CROSSHAIR_LINE_THICK, CROSSHAIR_LINE_LEN);
}
