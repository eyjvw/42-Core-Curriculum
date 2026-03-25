/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:47:41 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/19 19:02:41 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

int	mouse_move(int x, int y, t_game *game)
{
	static int	s_x;

	(void) y;
	if (s_x < x)
		turn_right(game, x - s_x, true);
	else if (s_x > x)
		turn_left(game, s_x - x, true);
	s_x = x;
	return (1);
}

void	turn_left(t_game *game, int diff, bool mouse)
{
	if (mouse)
		game->player.angle -= 0.004 * diff;
	else
		game->player.angle -= ROTATE_SPEED;
	game->player.dir.x = cos(game->player.angle);
	game->player.dir.y = sin(game->player.angle);
	game->player.cplane.x = -game->player.dir.y;
	game->player.cplane.y = game->player.dir.x;
}

void	turn_right(t_game *game, int diff, bool mouse)
{
	if (mouse)
		game->player.angle += 0.004 * diff;
	else
		game->player.angle += ROTATE_SPEED;
	game->player.dir.x = cos(game->player.angle);
	game->player.dir.y = sin(game->player.angle);
	game->player.cplane.x = -game->player.dir.y;
	game->player.cplane.y = game->player.dir.x;
}
