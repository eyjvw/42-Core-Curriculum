/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:56:49 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:39:05 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"

void	replace_doors(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->door_curr)
		data->map[data->doors[i].y][data->doors[i].x] = 'D';
}

void	add_door(t_data *data, int x, int y)
{
	if (data->door_curr + 1 == data->door_tot)
	{
		data->doors = ft_realloc(data->doors,
				sizeof(t_door) * data->door_tot,
				(sizeof(t_door) * data->door_tot) * 2);
		data->door_tot *= 2;
	}
	data->doors[data->door_curr].x = x;
	data->doors[data->door_curr].y = y;
	data->door_curr++;
}
