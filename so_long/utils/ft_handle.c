/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 07:30:26 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/11 05:59:54 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_handle_close(t_game *game)
{
	ft_psuccess(SUCCESS_CLOSE);
	ft_clean_exit(game, 0);
	return (0);
}

int	ft_handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		ft_handle_close(game);
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		game->player = game->player_up;
		ft_move_player(game, 0, -1);
	}
	if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		game->player = game->player_left;
		ft_move_player(game, -1, 0);
	}
	if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		game->player = game->player_down;
		ft_move_player(game, 0, 1);
	}
	if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		game->player = game->player_right;
		ft_move_player(game, 1, 0);
	}
	return (0);
}
