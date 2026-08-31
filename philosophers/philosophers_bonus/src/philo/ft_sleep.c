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

/*
** Death is watched by the monitor thread, so sleeping only has to wake up
** often enough for the process to stay responsive.
*/
void	ft_sleep(t_philo *philo, long long ms)
{
	long long	start;

	start = ft_timestamp(philo->data);
	while (ft_timestamp(philo->data) - start < ms)
		usleep(200);
}
