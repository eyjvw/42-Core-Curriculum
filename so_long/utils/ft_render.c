/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 04:51:50 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/11 05:59:19 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_texture	*ft_get_texture(t_game *game, char tile)
{
	if (tile == '1')
		return (&game->wall);
	else if (tile == '0')
		return (&game->floor);
	else if (tile == 'C')
		return (&game->collectible);
	else if (tile == 'E')
		return (&game->exit_door);
	else if (tile == 'P')
		return (&game->player);
	else if (tile == 'M')
		return (&game->mob);
	return (NULL);
}

static void	ft_draw(t_game *game, int x, int y, char tile)
{
	t_texture	*texture;
	int			px;
	int			py;

	texture = ft_get_texture(game, tile);
	if (!texture)
		return ;
	px = x * TILE_SIZE;
	py = y * TILE_SIZE;
	mlx_put_image_to_window(game->mlx, game->win, texture->img, px, py);
	if (game->player_on_exit && tile == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->player.img, px, py);
}

void	ft_stats(t_game *game)
{
	char	*str;

	str = ft_fusion("Mouvements : ", game->moves);
	if (!str)
		return ;
	mlx_string_put(game->mlx, game->win, 10, 10, 0x000000, str);
	free(str);
	str = ft_fusion("Collectibles collectes : ",
			game->collectibles_collected);
	if (!str)
		return ;
	mlx_string_put(game->mlx, game->win, 10, 20, 0x000000, str);
	free(str);
}

void	ft_render(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			ft_draw(game, x, y, game->map->map[y][x]);
			x++;
		}
		y++;
	}
	ft_stats(game);
}
