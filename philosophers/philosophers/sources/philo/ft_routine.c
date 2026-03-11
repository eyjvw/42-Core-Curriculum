/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:20:55 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 08:54:58 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, TAKEN_FORK);
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	if (ft_get_death(philo->data))
		return (pthread_mutex_unlock(first), (void)0);
	ft_print(philo, TAKEN_FORK);
	pthread_mutex_lock(second);
	if (ft_get_death(philo->data))
		return (pthread_mutex_unlock(second), pthread_mutex_unlock(first), (void)0);
	ft_print(philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->data->meal);
	philo->last_meal_time = ft_timestamp(philo->data);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal);
	ft_print(philo, EATING);
	ft_sleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

static void	ft_sleep_think(t_philo *philo)
{
	if (!ft_get_death(philo->data))
	{
		ft_print(philo, SLEEPING);
		ft_sleep(philo->data, philo->data->time_to_sleep);
	}
	if (!ft_get_death(philo->data))
		ft_print(philo, THINKING);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
		return (ft_one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(100);
	while (!ft_get_death(philo->data))
	{
		ft_eat(philo);
		ft_sleep_think(philo);
	}
	return (NULL);
}
