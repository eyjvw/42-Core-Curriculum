/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timestamp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:08:56 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 08:54:55 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_timestamp(t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_print_error(&data->print, GETTIMEOFDAY_ERROR);
		ft_set_death(data);
		return (data->start_time);
	}
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}
