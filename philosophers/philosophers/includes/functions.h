/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:31:33 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 09:11:09 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "structs.h"
#include <stdbool.h>

void		*ft_routine(void *arg);

void		ft_parsing(t_data *data, int ac, char **av);
void		ft_init(t_data *data);
void		ft_clean(t_data *data);
void		ft_print_error(pthread_mutex_t *mutex, char *s);
void		ft_print(t_philo *philo, char *s);
void		ft_sleep(t_data *data, long long ms);
void		ft_monitor(t_data *data);
void		ft_join(t_data *data);
void		ft_set_death(t_data *data);

int			ft_atoi(char *s);

bool		ft_get_death(t_data *data);

long long	ft_atoll(char *s);
long long	ft_timestamp(t_data *data);
