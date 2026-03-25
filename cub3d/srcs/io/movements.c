/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:53:11 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 18:32:28 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	move_forward(t_game *game)
{
	game->player.pos.x += game->player.dir.x * MOVE_SPEED;
	if (is_wall(game->data.map,
			(int)game->player.pos.x,
			(int)game->player.pos.y))
		game->player.pos.x -= game->player.dir.x * MOVE_SPEED;
	game->player.pos.y += game->player.dir.y * MOVE_SPEED;
	if (is_wall(game->data.map,
			(int)game->player.pos.x,
			(int)game->player.pos.y))
		game->player.pos.y -= game->player.dir.y * MOVE_SPEED;
}

void	move_backward(t_game *game)
{
	game->player.pos.x += -game->player.dir.x * MOVE_SPEED;
	if (is_wall(game->data.map,
			(int)game->player.pos.x,
			(int)game->player.pos.y))
		game->player.pos.x -= -game->player.dir.x * MOVE_SPEED;
	game->player.pos.y += -game->player.dir.y * MOVE_SPEED;
	if (is_wall(game->data.map,
			(int)game->player.pos.x,
			(int)game->player.pos.y))
		game->player.pos.y -= -game->player.dir.y * MOVE_SPEED;
}

void	move_right(t_game *game)
{
	game->player.pos.x += game->player.cplane.x * MOVE_SPEED;
	game->player.pos.y += game->player.cplane.y * MOVE_SPEED;
	if (is_wall(game->data.map,
			(int)game->player.pos.x,
			(int)game->player.pos.y))
	{
		game->player.pos.x -= game->player.cplane.x * MOVE_SPEED;
		game->player.pos.y -= game->player.cplane.y * MOVE_SPEED;
	}
}

void	move_left(t_game *game)
{
	game->player.pos.x += -game->player.cplane.x * MOVE_SPEED;
	game->player.pos.y += -game->player.cplane.y * MOVE_SPEED;
	if (is_wall(game->data.map,
			(int)game->player.pos.x,
			(int)game->player.pos.y))
	{
		game->player.pos.x -= -game->player.cplane.x * MOVE_SPEED;
		game->player.pos.y -= -game->player.cplane.y * MOVE_SPEED;
	}
}
