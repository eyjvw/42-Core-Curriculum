/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:31:25 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 09:11:50 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <pthread.h>
#include <stdbool.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;

	bool			done;

	pthread_t		thread_id;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

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

	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	meal;

	struct s_philo	*philos;
}	t_data;
