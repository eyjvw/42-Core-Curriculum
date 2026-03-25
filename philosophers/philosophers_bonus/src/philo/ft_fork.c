/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 04:07:46 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:20:27 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
		{
			ft_kill_all(data);
			ft_clean(data, true);
			exit(EXIT_FAILURE);
		}
		if (data->pids[i] == 0)
			ft_routine(&data->philos[i]);
		i++;
	}
}
