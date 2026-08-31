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

#include "philosophers.h"

static int	ft_putnbr(char *buf, int i, long long n)
{
	if (n >= 10)
		i = ft_putnbr(buf, i, n / 10);
	buf[i] = '0' + (n % 10);
	return (i + 1);
}

/*
** One "timestamp id state" line, emitted with a single write() so that two
** logs can never interleave, and so that nothing stays stuck in a stdio
** buffer if the process is killed.
*/
static void	ft_log(t_data *data, int id, long long now, char *s)
{
	char	buf[128];
	int		i;

	i = ft_putnbr(buf, 0, now - data->start_time);
	buf[i++] = ' ';
	i = ft_putnbr(buf, i, id);
	buf[i++] = ' ';
	while (*s)
		buf[i++] = *s++;
	buf[i++] = '\n';
	write(1, buf, i);
}

void	ft_print(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print);
	if (!ft_get_death(philo->data))
		ft_log(philo->data, philo->id, ft_timestamp(philo->data), s);
	pthread_mutex_unlock(&philo->data->print);
}

void	ft_print_death(t_data *data, int id, long long now)
{
	pthread_mutex_lock(&data->print);
	ft_log(data, id, now, DIED);
	pthread_mutex_unlock(&data->print);
}
