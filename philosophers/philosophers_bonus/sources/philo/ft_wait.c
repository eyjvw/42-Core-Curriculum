/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 04:03:25 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/02 05:24:22 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_wait(t_data *data)
{
	int	finished;
	int	status;

	if (data->must_eat == -1)
	{
		sem_wait(data->dead);
		ft_kill_all(data);
	}
	else
	{
		finished = 0;
		while (finished < data->num_philos)
		{
			if (waitpid(-1, &status, 0) == -1)
				break ;
			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
				finished++;
			else
			{
				ft_kill_all(data);
				break ;
			}
		}
	}
}
