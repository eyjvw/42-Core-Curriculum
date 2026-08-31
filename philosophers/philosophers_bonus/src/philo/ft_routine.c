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
	ft_sleep(philo, philo->data->time_to_die);
	sem_post(philo->data->forks);
	ft_die(philo);
}

static void	ft_eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_print(philo, TAKEN_FORK);
	sem_wait(philo->data->forks);
	ft_print(philo, TAKEN_FORK);
	sem_wait(philo->data->meal);
	philo->last_meal_time = ft_timestamp(philo->data);
	philo->meals_eaten++;
	sem_post(philo->data->meal);
	ft_print(philo, EATING);
	ft_sleep(philo, philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

/*
** Thinking is not instantaneous: a philosopher that grabs its forks again the
** moment it drops them can starve a neighbour. Waiting for half of the slack
** left by a full eat/sleep cycle keeps every philosopher served well inside
** time_to_die, even with 200 of them.
*/
static void	ft_sleep_think(t_philo *philo)
{
	long long	think;

	ft_print(philo, SLEEPING);
	ft_sleep(philo, philo->data->time_to_sleep);
	ft_print(philo, THINKING);
	think = philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep;
	if (think > 0)
		ft_sleep(philo, think / 2);
}

static bool	ft_is_full(t_philo *philo)
{
	bool	full;

	sem_wait(philo->data->meal);
	full = (philo->data->must_eat != -1
			&& philo->meals_eaten >= philo->data->must_eat);
	philo->done = full;
	sem_post(philo->data->meal);
	return (full);
}

void	ft_routine(t_philo *philo)
{
	pthread_t	monitor;

	if (philo->data->num_philos == 1)
		return (ft_one_philo(philo));
	if (philo->id % 2 == 0)
		ft_sleep(philo, philo->data->time_to_eat);
	if (pthread_create(&monitor, NULL, ft_monitor, philo) != 0)
		ft_child_exit(philo, EXIT_FAILURE);
	while (1)
	{
		ft_eat(philo);
		if (ft_is_full(philo))
			break ;
		ft_sleep_think(philo);
	}
	pthread_join(monitor, NULL);
	ft_child_exit(philo, PHILO_DONE);
}
