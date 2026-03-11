/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 02:05:55 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 08:43:17 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_kill_all(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->pids && data->pids[i] > 0)
			kill(data->pids[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (data->pids && data->pids[i] > 0)
			waitpid(data->pids[i], &status, 0);
		i++;
	}
}
