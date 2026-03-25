/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:40:38 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:11:14 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "others.h"

bool	is_wall(char **map, int x, int y)
{
	return (map[y][x] == 'O' || map[y][x] == '1' || is_door(map, x, y));
}

int	rgb_to_hex(uint8_t *rgb)
{
	return (((rgb[R] & 0xff) << 16)
		+ ((rgb[G] & 0xff) << 8) + (rgb[B] & 0xff));
}

float	angle_to_radian(int angle)
{
	return (angle * (PI / 180.0));
}
