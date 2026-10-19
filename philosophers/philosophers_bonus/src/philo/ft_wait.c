/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 04:03:25 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:20:44 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
** Forgets a child that has already been reaped, so that ft_kill_all() never
** signals or waits for a pid that the system may since have reused.
*/
static void	ft_forget(t_data *data, pid_t pid)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->pids[i] == pid)
			data->pids[i] = -1;
		i++;
	}
}

/*
** A philosopher only exits on its own with PHILO_DONE, once it has eaten
** enough. Any other end (a death, an error, a crash) stops the whole
** simulation, whether or not a must-eat count was given.
*/
void	ft_wait(t_data *data)
{
	int		finished;
	int		status;
	pid_t	pid;

	finished = 0;
	while (finished < data->num_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		ft_forget(data, pid);
		if (!WIFEXITED(status) || WEXITSTATUS(status) != PHILO_DONE)
		{
			ft_kill_all(data);
			break ;
		}
		finished++;
	}
}
