/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:45:37 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/08 03:44:59 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"

static bool	rgb_standard(uint16_t *rgb_data)
{
	return (rgb_data[LEN] <= RGB_LEN_MAX
		&& rgb_data[FIELD_VALUE] <= EIGHT_BITS_MAX
		&& rgb_data[FIELD_LEN] <= RGB_FIELD_LEN_MAX
		&& rgb_data[FIELD_COUNT] <= RGB_MAX_FIELD);
}

static void	update_field(const char *color, uint16_t *rgb_data)
{
	rgb_data[FIELD_VALUE] += *color - '0';
	if (ft_isdigit(*(color + 1)))
		rgb_data[FIELD_VALUE] *= 10;
	rgb_data[FIELD_LEN]++;
}

static void	reset_field(t_data *data, int8_t id, uint16_t *rgb_data)
{
	data->colors[id][rgb_data[FIELD_COUNT] - 1] = rgb_data[FIELD_VALUE];
	rgb_data[FIELD_VALUE] = 0;
	rgb_data[FIELD_LEN] = 0;
	rgb_data[FIELD_COUNT]++;
}

static bool	check_rgb(uint16_t *rgb_data, const char *color, size_t line)
{
	if (rgb_data[FIELD_LEN] && rgb_data[FIELD_COUNT] == 3
		&& !*color && rgb_standard(rgb_data))
		return (true);
	else
		return (parse_error(INVALID, COLOR, line), false);
}

bool	check_color(const char *color, size_t line, t_data *data, int8_t id)
{
	uint8_t		i;
	uint16_t	rgb_data[4];

	if (id == -1)
		return (false);
	i = 0;
	while (i < 3)
		rgb_data[i++] = 0;
	rgb_data[FIELD_COUNT] = 1;
	while (*color && (ft_isdigit(*color) || *color == ',')
		&& rgb_standard(rgb_data))
	{
		if (*color == ',')
		{
			if (rgb_data[FIELD_LEN] == 0)
				return (false);
			reset_field(data, id, rgb_data);
		}
		else
			update_field(color, rgb_data);
		rgb_data[LEN]++;
		color++;
	}
	data->colors[id][rgb_data[FIELD_COUNT] - 1] = rgb_data[FIELD_VALUE];
	return (check_rgb(rgb_data, color, line));
}
