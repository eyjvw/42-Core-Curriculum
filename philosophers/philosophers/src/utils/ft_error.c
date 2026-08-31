/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 12:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/08/31 12:00:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/*
** The length is computed as it writes, one byte at a time: a plain
** strlen()-shaped loop gets recognised by the optimiser and turned into a call
** to strlen(), which is not part of the functions this project may use.
*/
static void	ft_putstr_fd(int fd, char *s)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
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
