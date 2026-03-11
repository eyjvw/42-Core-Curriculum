/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:07:32 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 08:54:49 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

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

void	ft_print_error(pthread_mutex_t *mutex, char *s)
{
	if (mutex)
		pthread_mutex_lock(mutex);
	ft_putstr_fd(2, RED);
	ft_putstr_fd(2, s);
	ft_putstr_fd(2, RESET);
	if (mutex)
		pthread_mutex_unlock(mutex);
}

void	ft_print(t_philo *philo, char *s)
{
	if (!ft_get_death(philo->data))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%4lld %6d %s\n",
			ft_timestamp(philo->data) - philo->data->start_time, philo->id, s);
		pthread_mutex_unlock(&philo->data->print);
	}
}
