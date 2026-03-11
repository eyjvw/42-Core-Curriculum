/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:31:25 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 09:10:23 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <semaphore.h>
#include <stdbool.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;

	long long		last_meal_time;

	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				someone_died;
	int				must_eat;

	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;

	sem_t			*forks;
	sem_t			*print;
	sem_t			*dead;

	struct s_philo	*philos;

	pid_t			*pids;
}	t_data;
