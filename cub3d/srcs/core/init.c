/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:37:51 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/19 18:42:21 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	init_dir(t_game *game)
{
	int	i;

	i = -1;
	game->player.dir.y = 0;
	game->player.dir.x = 0;
	if (game->data.player_dir == 'N')
		game->player.dir.y--;
	else if (game->data.player_dir == 'S')
		game->player.dir.y++;
	else if (game->data.player_dir == 'E')
		game->player.dir.x++;
	else if (game->data.player_dir == 'W')
		game->player.dir.x--;
	while (++i < KEY_AMOUNT)
		game->keys[i] = false;
}

static void	init_angle(t_game *game)
{
	if (game->data.player_dir == 'N')
		game->player.angle = -(PI / 2);
	else if (game->data.player_dir == 'S')
		game->player.angle = -(3 * PI / 2);
	else if (game->data.player_dir == 'E')
		game->player.angle = -(2 * PI);
	else if (game->data.player_dir == 'W')
		game->player.angle = (PI);
}

static void	player_init(t_game *game, t_point data)
{
	init_dir(game);
	init_angle(game);
	game->time = get_time();
	game->player.pos.x = data.x + 0.5;
	game->player.pos.y = data.y + 0.5;
	game->player.cplane.y = game->player.dir.x;
	game->player.cplane.x = -game->player.dir.y;
	game->mouse = true;
}

void	game_init(char *file, t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	if (!dump(file, &game->data))
		ft_kill(game, EXIT_FAILURE);
	if (!init_display(&game->display, &game->data))
		ft_kill(game, EXIT_FAILURE);
	player_init(game, get_point(game->data.player_x, game->data.player_y));
}
