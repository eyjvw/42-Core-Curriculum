/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:09:44 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:19:59 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	ft_init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		ft_print_error(NULL, PHILOS_MALLOC_FAILED);
		ft_clean(data, true);
		exit(EXIT_FAILURE);
	}
	i = 0;
	data->start_time = ft_timestamp(data);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].done = false;
		data->philos[i].data = data;
		i++;
	}
}

static void	ft_init_pids(t_data *data)
{
	int	i;

	data->pids = malloc(sizeof(pid_t) * data->num_philos);
	if (!data->pids)
	{
		ft_print_error(NULL, PIDS_MALLOC_FAILED);
		ft_clean(data, true);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < data->num_philos)
	{
		data->pids[i] = -1;
		i++;
	}
}

static void	ft_unlink_sems(void)
{
	sem_unlink(SEM_FOR_FORKS);
	sem_unlink(SEM_FOR_PRINT);
	sem_unlink(SEM_FOR_MEAL);
}

/*
** The names are unlinked again as soon as the semaphores are open: the
** children inherit the semaphores themselves through fork(), so nothing needs
** the names any more, and none is left behind in /dev/shm even when the
** program is killed by a signal it is not allowed to catch.
*/
void	ft_init(t_data *data)
{
	ft_unlink_sems();
	data->forks = sem_open(SEM_FOR_FORKS, O_CREAT, 0664, data->num_philos);
	data->print = sem_open(SEM_FOR_PRINT, O_CREAT, 0664, 1);
	data->meal = sem_open(SEM_FOR_MEAL, O_CREAT, 0664, 1);
	ft_unlink_sems();
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED
		|| data->meal == SEM_FAILED)
	{
		ft_print_error(NULL, "sem_open failed\n");
		ft_clean(data, true);
		exit(EXIT_FAILURE);
	}
	ft_init_pids(data);
	ft_init_philos(data);
}
