/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 05:39:09 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/08 05:46:03 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_free_texture(t_game *game, t_texture *texture)
{
	if (!game || !game->mlx || !texture || !texture->img)
		return ;
	mlx_destroy_image(game->mlx, texture->img);
	texture->img = NULL;
}

static void	ft_free_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	ft_free_texture(game, &game->wall);
	ft_free_texture(game, &game->floor);
	ft_free_texture(game, &game->player_down);
	ft_free_texture(game, &game->player_up);
	ft_free_texture(game, &game->player_left);
	ft_free_texture(game, &game->player_right);
	ft_free_texture(game, &game->collectible);
	ft_free_texture(game, &game->exit_door);
	ft_free_texture(game, &game->mob);
}

void	ft_clean_exit(t_game *game, int code)
{
	unsigned long	i;

	if (!game)
		exit(code);
	ft_free_textures(game);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	if (game->mlx)
	{
		(mlx_destroy_display(game->mlx), free(game->mlx));
		game->mlx = NULL;
	}
	if (game->map)
	{
		if (game->map->map)
		{
			i = 0;
			while (game->map->map[i])
				(free(game->map->map[i]), game->map->map[i++] = NULL);
			(free(game->map->map), game->map->map = NULL);
		}
		(free(game->map), game->map = NULL);
	}
	exit(code);
}
