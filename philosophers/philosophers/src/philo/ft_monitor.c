/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:30:01 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 09:17:17 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	ft_check_one_dead(t_data *data)
{
	int			i;
	long long	now;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal);
		if (data->philos[i].done)
		{
			(pthread_mutex_unlock(&data->meal), i++);
			continue ;
		}
		now = ft_timestamp(data);
		if (now - data->philos[i].last_meal_time > data->time_to_die)
		{
			(pthread_mutex_unlock(&data->meal), ft_set_death(data));
			ft_print_death(data, data->philos[i].id, now);
			return (1);
		}
		pthread_mutex_unlock(&data->meal);
		i++;
	}
	return (0);
}

static bool	ft_check_all_eaten(t_data *data)
{
	int	i;
	int	done_count;

	if (data->must_eat <= 0)
		return (0);
	i = 0;
	done_count = 0;
	pthread_mutex_lock(&data->meal);
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten >= data->must_eat)
		{
			data->philos[i].done = 1;
			done_count++;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal);
	if (done_count == data->num_philos)
	{
		ft_set_death(data);
		return (1);
	}
	return (0);
}

void	ft_monitor(t_data *data)
{
	while (1)
	{
		if (ft_check_one_dead(data) || ft_check_all_eaten(data))
			return ;
		usleep(800);
	}
}
