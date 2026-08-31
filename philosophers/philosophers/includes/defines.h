/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:30:37 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 09:10:52 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"

#define INVALID_NUM_ARGS "Invalid number of arguments\n"
#define INVALID_ARGS "Invalid arguments\n"
#define NUM_PHILO_LIMITS "Philosophers must be between 1 and 200\n"
#define FORKS_MALLOC_FAILED "Allocation of the forks failed\n"
#define PHILOS_MALLOC_FAILED "Allocation of the philosophers failed\n"
#define GETTIMEOFDAY_ERROR "gettimeofday failed\n"
#define NEGATIVE_ARGS "The arguments must be positive\n"

#define THINKING "is thinking"
#define TAKEN_FORK "has taken a fork"
#define EATING "is eating"
#define SLEEPING "is sleeping"
#define DIED "died"
