/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:29:48 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/11 20:53:04 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->doors = calloc(DOOR_BASE_AMOUNT, sizeof(t_door));
	if (!data->doors)
		system_error(MALLOC);
	data->door_tot = DOOR_BASE_AMOUNT;
}

void	delete_data(t_data *data)
{
	uint8_t	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
		data->map = NULL;
	}
	i = 0;
	while (i < TEXTURE_AMOUNT)
	{
		if (data->texture_path[i])
		{
			free(data->texture_path[i]);
			data->texture_path[i] = NULL;
		}
		i++;
	}
	if (data->doors)
	{
		free(data->doors);
		data->doors = NULL;
	}
}
