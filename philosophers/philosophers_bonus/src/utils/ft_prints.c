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

static int	ft_putnbr(char *buf, int i, long long n)
{
	if (n >= 10)
		i = ft_putnbr(buf, i, n / 10);
	buf[i] = '0' + (n % 10);
	return (i + 1);
}

/*
** One "timestamp id state" line, emitted with a single write(). Philosophers
** are separate processes that get killed when the simulation ends, so no log
** may be left sitting in a stdio buffer.
*/
static void	ft_log(t_philo *philo, char *s)
{
	char	buf[128];
	int		i;

	i = ft_putnbr(buf, 0, ft_timestamp(philo->data) - philo->data->start_time);
	buf[i++] = ' ';
	i = ft_putnbr(buf, i, philo->id);
	buf[i++] = ' ';
	while (*s)
		buf[i++] = *s++;
	buf[i++] = '\n';
	write(1, buf, i);
}

void	ft_print(t_philo *philo, char *s)
{
	sem_wait(philo->data->print);
	ft_log(philo, s);
	sem_post(philo->data->print);
}

/*
** The print semaphore is taken and never released: once the death line is out,
** no other philosopher can append a message after it.
*/
void	ft_die(t_philo *philo)
{
	sem_wait(philo->data->print);
	ft_log(philo, DIED);
	sem_post(philo->data->dead);
	ft_child_exit(philo, PHILO_DIED);
}
