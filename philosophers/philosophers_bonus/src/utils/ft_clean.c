/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:06:46 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:19:57 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_clean(t_data *data, bool unlink)
{
	if (data->pids)
		free(data->pids);
	if (data->philos)
		free(data->philos);
	if (data->forks && data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->print && data->print != SEM_FAILED)
		sem_close(data->print);
	if (data->dead && data->dead != SEM_FAILED)
		sem_close(data->dead);
	if (unlink)
	{
		sem_unlink(SEM_FOR_FORKS);
		sem_unlink(SEM_FOR_PRINT);
		sem_unlink(SEM_FOR_DEAD);
	}
}

void	ft_child_exit(t_philo *philo, int status)
{
	ft_clean(philo->data, false);
	exit(status);
}
