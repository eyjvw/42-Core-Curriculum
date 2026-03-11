/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:30:01 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 09:03:14 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_timestamp(philo->data) - philo->last_meal_time
			> philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("%4lld %6d died\n",
				ft_timestamp(philo->data) - philo->data->start_time, philo->id);
			sem_post(philo->data->dead);
			ft_child_exit(philo, PHILO_DIED);
		}
		usleep(200);
	}
	return (NULL);
}
