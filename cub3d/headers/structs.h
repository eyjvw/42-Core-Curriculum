/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:04:32 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 21:01:43 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdint.h>
# include <stdbool.h>
# include "cub_interpreter.h"

# define KEY_AMOUNT		8

typedef struct s_ray		t_ray;
typedef struct s_tex		t_tex;
typedef struct s_img		t_img;
typedef struct s_game		t_game;
typedef struct s_point		t_point;
typedef struct s_ddata		t_ddata;
typedef struct s_ipoint		t_ipoint;
typedef struct s_player		t_player;
typedef struct s_sprite		t_sprite;
typedef struct s_display	t_display;

typedef struct s_ipoint
{
	int	x;
	int	y;
}	t_ipoint;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
}	t_img;

typedef struct s_sprite
{
	int		frame_amount;
	int		current_frame;
	t_img	*frames;
}	t_sprite;

typedef struct s_tex
{
	t_ipoint	coo;
	t_img		*img;
	int			color;
	double		step;
	double		pos;
}	t_tex;

typedef struct s_display
{
	void		*main;
	void		*window;
	t_img		frame;
	t_img		minimap;
	int			map_tidle_size;
	t_img		texture[TEXTURE_AMOUNT];
	t_sprite	gun;
}	t_display;

typedef struct s_ddata
{
	bool		side;
	t_ipoint	map;
	t_ipoint	step;
	t_point		delta;
	t_point		hit_pos;
	t_point		side_dist;
	float		wall_dist;
	float		wall_x;
}	t_ddata;

typedef struct s_ray
{
	t_point	dir;
	int		id;
	int		line_start;
	int		line_end;
	int		line_len;
}	t_ray;

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	t_point	cplane;
	float	angle;
}	t_player;

typedef struct s_game
{
	uint32_t	time;
	t_ddata		dda;
	t_ddata		ddoor;
	t_data		data;
	t_player	player;
	t_display	display;
	bool		mouse;
	bool		keys[KEY_AMOUNT];
}	t_game;

#endif
