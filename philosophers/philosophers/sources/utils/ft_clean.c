/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:06:46 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 08:54:53 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_clean(t_data *data)
{
	int	i;

	if (data->philos)
		free(data->philos);
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead);
}
