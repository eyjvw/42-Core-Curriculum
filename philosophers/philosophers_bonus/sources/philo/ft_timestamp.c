/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timestamp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:08:56 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/02 04:33:24 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_timestamp(t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_print_error(data->print, GETTIMEOFDAY_ERROR);
		sem_post(data->dead);
		exit(EXIT_FAILURE);
	}
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}
