/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:20:55 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:20:36 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	ft_one_philo(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_print(philo, TAKEN_FORK);
	usleep(philo->data->time_to_die * 1000);
	ft_print(philo, DIED);
	sem_post(philo->data->forks);
	sem_post(philo->data->dead);
	ft_child_exit(philo, PHILO_DIED);
}

static void	ft_eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_print(philo, TAKEN_FORK);
	sem_wait(philo->data->forks);
	ft_print(philo, TAKEN_FORK);
	philo->last_meal_time = ft_timestamp(philo->data);
	ft_print(philo, EATING);
	philo->meals_eaten++;
	ft_sleep(philo, philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static void	ft_sleep_think(t_philo *philo)
{
	ft_print(philo, SLEEPING);
	ft_sleep(philo, philo->data->time_to_sleep);
	ft_print(philo, THINKING);
}

void	ft_routine(t_philo *philo)
{
	pthread_t	monitor;

	if (philo->data->num_philos == 1)
		return (ft_one_philo(philo));
	if (philo->id % 2 == 0)
		usleep(2000);
	if (pthread_create(&monitor, NULL, ft_monitor, philo) != 0)
		ft_child_exit(philo, EXIT_FAILURE);
	while (1)
	{
		ft_eat(philo);
		if (philo->data->must_eat != -1
			&& philo->meals_eaten >= philo->data->must_eat)
		{
			pthread_cancel(monitor);
			pthread_join(monitor, NULL);
			ft_child_exit(philo, PHILO_DONE);
		}
		ft_sleep_think(philo);
	}
}
