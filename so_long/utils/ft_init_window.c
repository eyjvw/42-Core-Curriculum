/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 01:38:57 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/11 05:59:40 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_init_window(t_game *game)
{
	int	screen_w;
	int	screen_h;

	game->mlx = mlx_init();
	if (!game->mlx)
		(ft_perror(ERR_MLX_INIT),
			ft_clean_exit(game, 1));
	mlx_get_screen_size(game->mlx, &screen_w, &screen_h);
	if (game->map->width > screen_w / TILE_SIZE
		|| game->map->height > screen_h / TILE_SIZE)
		(ft_perror(ERR_TOO_BIG), ft_clean_exit(game, 1));
	game->win = mlx_new_window(game->mlx, game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE, "so_long");
	if (!game->win)
		(ft_perror(ERR_WINDOW),
			ft_clean_exit(game, 1));
	ft_psuccess(SUCCESS_WINDOW);
	ft_load_textures(game);
	ft_render(game);
	mlx_hook(game->win, 2, 1L << 0,
		(int (*)())(void (*)(void))ft_handle_key, game);
	mlx_hook(game->win, 17, 0L,
		(int (*)())(void (*)(void))ft_handle_close, game);
	mlx_expose_hook(game->win, (int (*)(void *))ft_handle_expose, game);
	mlx_loop(game->mlx);
}
