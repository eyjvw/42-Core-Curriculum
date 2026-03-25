/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 05:36:42 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/22 14:21:45 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"

bool	check_player(char c, size_t line_n)
{
	static bool	player = false;

	if (ft_isset(c, PLAYER_SET))
	{
		if (player)
			return (parse_error(DUPLICATE, PLAYER, line_n), false);
		player = true;
	}
	return (true);
}

bool	check_map_line(char *line, size_t line_n)
{
	uint32_t		i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isset(line[i], MAP_SET) || !check_player(line[i], line_n))
		{
			parse_error(INVALID, MAP, line_n);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	flood_fill(t_data *data, int x, int y, bool *closed)
{
	if (x < 0 || y < 0
		|| !data->map[y]
		|| y > (int)ft_doublelen(data->map)
		|| x > (int)ft_strlen(data->map[y])
		|| !data->map[y][x]
		|| data->map[y][x] == '\n' || data->map[y][x] == ' ')
	{
		if (*closed)
			parse_error(INVALID, MAP, y + 1);
		*closed = false;
		return (closed);
	}
	else if (data->map[y][x] == '1' || data->map[y][x] == 'x')
		return (true);
	if (data->map[y][x] == 'D')
		add_door(data, x, y);
	data->map[y][x] = 'x';
	flood_fill(data, x + 1, y, closed);
	flood_fill(data, x - 1, y, closed);
	flood_fill(data, x, y + 1, closed);
	flood_fill(data, x, y - 1, closed);
	return (*closed);
}

bool	find_player(t_data *data)
{
	ssize_t	x;
	ssize_t	y;

	x = -1;
	y = -1;
	while (data->map[++x])
	{
		while (data->map[x][++y])
		{
			if (ft_isset(data->map[x][y], PLAYER_SET))
			{
				data->player_dir = data->map[x][y];
				data->player_y = x;
				data->player_x = y;
				return (true);
			}
		}
		y = -1;
	}
	return (parse_error(MISSING, PLAYER, 0), false);
}
