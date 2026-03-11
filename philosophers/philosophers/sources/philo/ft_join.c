/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:35:24 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 08:55:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}
