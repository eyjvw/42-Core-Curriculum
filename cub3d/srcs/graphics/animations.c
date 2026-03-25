/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:06:43 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:38:39 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	update_gun(t_game *game, t_sprite *gun)
{
	gun->current_frame++;
	if (gun->current_frame == gun->frame_amount)
	{
		gun->current_frame = 0;
		game->keys[MCLICKL_ID] = false;
	}
	if (game->data.map[game->ddoor.map.y][game->ddoor.map.x] == 'D'
		&& gun->current_frame == 4)
		game->data.map[game->ddoor.map.y][game->ddoor.map.x] = 'x';
}
