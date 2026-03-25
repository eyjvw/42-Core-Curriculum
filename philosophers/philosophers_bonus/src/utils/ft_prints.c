/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:07:32 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:20:05 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

static void	ft_putstr_fd(int fd, char *s)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_print_error(sem_t *sem, char *s)
{
	if (sem)
		sem_wait(sem);
	ft_putstr_fd(2, RED);
	ft_putstr_fd(2, s);
	ft_putstr_fd(2, RESET);
	if (sem)
		sem_post(sem);
}

void	ft_print(t_philo *philo, char *s)
{
	sem_wait(philo->data->print);
	printf("%4lld %6d %s\n",
		ft_timestamp(philo->data) - philo->data->start_time, philo->id, s);
	sem_post(philo->data->print);
}
