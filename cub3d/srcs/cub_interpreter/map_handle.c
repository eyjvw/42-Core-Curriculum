/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 01:20:29 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/19 18:19:17 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"

static bool	alloc_map(t_data *data)
{
	uint32_t	i;

	i = 0;
	data->map_size = MAP_BUFFER;
	data->map = malloc(sizeof(char **) * (data->map_size + 1));
	if (!data->map)
		return (system_error(MALLOC), false);
	while (i < data->map_size)
		data->map[i++] = NULL;
	return (true);
}

static bool	add_line(char *line, t_data *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->map_size && data->map[i])
		i++;
	if (i < data->map_size)
		data->map[i] = line;
	else
	{
		data->map = ft_double_realloc(data->map, data->map_size,
				data->map_size * 2);
		if (!data->map)
			return (system_error(MALLOC), false);
		data->map[i] = line;
		data->map_size *= 2;
	}
	return (true);
}

bool	check_map(int fd, char *line, size_t line_n, t_data *data)
{
	bool		ret;
	bool		valid;

	ret = true;
	valid = true;
	if (!line || !alloc_map(data))
		return (parse_error(MISSING, MAP, line_n), delete_data(data), false);
	while (line)
	{
		if (!check_map_line(line, line_n++))
			(free(line), ret = false);
		else
			add_line(line, data);
		line = get_next_line(fd);
	}
	if (!ret || !find_player(data)
		|| !flood_fill(data, data->player_x, data->player_y, &valid))
		return (delete_data(data), false);
	replace_doors(data);
	return (true);
}
