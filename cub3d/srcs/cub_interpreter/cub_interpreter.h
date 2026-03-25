/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_interpreter.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 02:02:19 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 15:25:43 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_INTERPRETER_H
# define CUB_INTERPRETER_H
# define TEXTURE_AMOUNT 5

typedef struct s_door
{
	int		x;
	int		y;
}	t_door;

typedef struct s_data
{
	char		**map;
	uint32_t	map_size;
	uint8_t		colors[2][3];
	char		*texture_path[TEXTURE_AMOUNT];
	char		player_dir;
	uint32_t	player_x;
	uint32_t	player_y;
	t_door		*doors;
	int			door_tot;
	int			door_curr;
}	t_data;

enum e_directions
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	DOOR
};

enum e_ydirections
{
	FLOOR,
	CEIL
};

enum e_colors
{
	R,
	G,
	B
};

//Process whole file
int		dump(char *file_path, t_data *data);

//Data structure
void	init_data(t_data *data);
void	delete_data(t_data *data);

//Doors
bool	is_door(char **map, int x, int y);

#endif
