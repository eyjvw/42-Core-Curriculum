/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:09:44 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 08:54:53 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		ft_print_error(NULL, FORKS_MALLOC_FAILED);
		ft_clean(data);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

static void	ft_init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		ft_print_error(NULL, PHILOS_MALLOC_FAILED);
		ft_clean(data);
		exit(EXIT_FAILURE);
	}
	i = 0;
	data->start_time = ft_timestamp(data);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		data->philos[i].done = 0;
		i++;
	}
}

static void	ft_init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, ft_routine,
				&data->philos[i]) != 0)
		{
			ft_set_death(data);
			while (--i >= 0)
				pthread_join(data->philos[i].thread_id, NULL);
			ft_clean(data);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_init(t_data *data)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->meal, NULL);
	ft_init_forks(data);
	ft_init_philos(data);
	ft_init_threads(data);
}
