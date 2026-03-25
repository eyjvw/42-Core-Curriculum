/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:28:15 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:20:39 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_sleep(t_philo *philo, long long ms)
{
	long long	start;

	start = ft_timestamp(philo->data);
	while (ft_timestamp(philo->data) - start < ms)
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
}
