/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:28:15 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 08:54:56 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_data *data, long long ms)
{
	long long	start;

	start = ft_timestamp(data);
	while (!ft_get_death(data) && ft_timestamp(data) - start < ms)
		usleep(100);
}
