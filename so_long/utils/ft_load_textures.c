/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 04:42:48 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/08 05:24:01 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_load(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_perror(ERR_CANT_LOAD);
		ft_putstr_fd(2, path);
		ft_putstr_fd(2, "\n");
		ft_clean_exit(game, 1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->size_len, &texture->endian);
	if (!texture->addr)
	{
		ft_perror(ERR_MLX_ADDR);
		ft_clean_exit(game, 1);
	}
}

void	ft_load_textures(t_game *game)
{
	ft_load(game, &game->wall, "textures/wall.xpm");
	ft_load(game, &game->floor, "textures/floor.xpm");
	ft_load(game, &game->player_down, "textures/player_down.xpm");
	ft_load(game, &game->player_up, "textures/player_up.xpm");
	ft_load(game, &game->player_left, "textures/player_left.xpm");
	ft_load(game, &game->player_right, "textures/player_right.xpm");
	ft_load(game, &game->collectible, "textures/collectible.xpm");
	ft_load(game, &game->exit_door, "textures/exit.xpm");
	ft_load(game, &game->mob, "textures/mob.xpm");
	game->player = game->player_down;
	ft_psuccess(SUCCESS_TEXTURES);
}
