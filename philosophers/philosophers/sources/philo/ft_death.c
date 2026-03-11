/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:37:50 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 08:55:01 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_set_death(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->dead);
}

bool	ft_get_death(t_data *data)
{
	bool	died;

	pthread_mutex_lock(&data->dead);
	died = data->someone_died;
	pthread_mutex_unlock(&data->dead);
	return (died);
}
