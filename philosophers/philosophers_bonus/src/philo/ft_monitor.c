/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:30:01 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:20:33 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
** Runs in a thread inside every philosopher process. The meal semaphore guards
** the two fields this thread shares with the routine thread (last_meal_time
** and done), so the child has no data race.
*/
void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->meal);
		if (philo->done)
			return (sem_post(philo->data->meal), NULL);
		if (ft_timestamp(philo->data) - philo->last_meal_time
			> philo->data->time_to_die)
		{
			sem_post(philo->data->meal);
			ft_die(philo);
		}
		sem_post(philo->data->meal);
		usleep(200);
	}
	return (NULL);
}
