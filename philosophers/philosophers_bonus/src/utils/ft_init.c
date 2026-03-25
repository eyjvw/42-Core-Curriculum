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

void	ft_init(t_data *data)
{
	sem_unlink(SEM_FOR_FORKS);
	sem_unlink(SEM_FOR_PRINT);
	sem_unlink(SEM_FOR_DEAD);
	data->forks = sem_open(SEM_FOR_FORKS, O_CREAT, 0664, data->num_philos);
	data->print = sem_open(SEM_FOR_PRINT, O_CREAT, 0664, 1);
	data->dead = sem_open(SEM_FOR_DEAD, O_CREAT, 0664, 0);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED
		|| data->dead == SEM_FAILED)
	{
		ft_print_error(NULL, "sem_open failed\n");
		ft_clean(data, true);
		exit(EXIT_FAILURE);
	}
	ft_init_pids(data);
	ft_init_philos(data);
}
