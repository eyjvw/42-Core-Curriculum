/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:31:33 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 09:03:14 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"
# include <stdbool.h>

void		ft_routine(t_philo *philo);
void		ft_parsing(t_data *data, int ac, char **av);
void		ft_init(t_data *data);
void		ft_clean(t_data *data, bool unlink);
void		ft_print_error(sem_t *sem, char *s);
void		ft_print(t_philo *philo, char *s);
void		ft_sleep(t_philo *philo, long long ms);
void		*ft_monitor(void *arg);
void		ft_kill_all(t_data *data);
void		ft_wait(t_data *data);
void		ft_fork(t_data *data);
void		ft_child_exit(t_philo *philo, int status);

int			ft_atoi(char *s);
long long	ft_atoll(char *s);
long long	ft_timestamp(t_data *data);

#endif
