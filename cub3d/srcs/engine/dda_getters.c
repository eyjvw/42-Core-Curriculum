/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:47:53 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:08:40 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_point	get_delta(t_point dir)
{
	t_point	delta;

	delta.x = 1e30;
	delta.y = 1e30;
	if (dir.x != 0)
		delta.x = fabs(1 / dir.x);
	if (dir.y != 0)
		delta.y = fabs(1 / dir.y);
	return (delta);
}

float	get_walldist(t_ddata *dda, t_point player, t_point dir)
{
	if (!dda->side)
		return ((dda->map.x - player.x + (1 - dda->step.x) / 2) / dir.x);
	return ((dda->map.y - player.y + (1 - dda->step.y) / 2) / dir.y);
}

float	get_wallx(t_ddata *dda, t_point dir, t_point player)
{
	float	wall_x;

	wall_x = player.x + dda->wall_dist * dir.x;
	if (dda->side == 0)
		wall_x = player.y + dda->wall_dist * dir.y;
	wall_x -= floor(dda->wall_x);
	return (wall_x);
}
