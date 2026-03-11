/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 04:21:28 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/11 05:59:33 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		collectibles;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
}	t_map;

typedef struct s_texture
{
	void	*addr;
	void	*img;
	int		bits_per_pixel;
	int		size_len;
	int		height;
	int		width;
	int		endian;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_texture	wall;
	t_texture	floor;
	t_texture	player;
	t_texture	player_up;
	t_texture	player_down;
	t_texture	player_right;
	t_texture	player_left;
	t_texture	collectible;
	t_texture	exit_door;
	t_texture	mob;
	int			moves;
	int			collectibles_collected;
	int			player_on_exit;
}	t_game;

#endif
