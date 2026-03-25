/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:01:17 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:20:02 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static bool	ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static void	ft_check_args(int ac, char **av)
{
	int	i;
	int	j;

	if ((ac < 5) || (ac > 6))
	{
		ft_print_error(NULL, INVALID_NUM_ARGS);
		exit(EXIT_FAILURE);
	}
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_is_digit(av[i][j]))
			{
				ft_print_error(NULL, INVALID_ARGS);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

static void	ft_set_values(t_data *data, int ac, char **av)
{
	data->forks = NULL;
	data->print = NULL;
	data->dead = NULL;
	data->pids = NULL;
	data->philos = NULL;
	data->num_philos = ft_atoi(av[1]);
	data->someone_died = 0;
	data->time_to_die = ft_atoll(av[2]);
	data->time_to_eat = ft_atoll(av[3]);
	data->time_to_sleep = ft_atoll(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
}

static void	ft_check_values(t_data *data)
{
	if (data->num_philos < 1 || data->num_philos > 200)
	{
		ft_print_error(NULL, NUM_PHILO_LIMITS);
		exit(EXIT_FAILURE);
	}
	if (data->time_to_die < 0)
	{
		ft_print_error(NULL, NEGATIVE_ARGS);
		exit(EXIT_FAILURE);
	}
	if (data->time_to_eat < 0)
	{
		ft_print_error(NULL, NEGATIVE_ARGS);
		exit(EXIT_FAILURE);
	}
	if (data->time_to_sleep < 0)
	{
		ft_print_error(NULL, NEGATIVE_ARGS);
		exit(EXIT_FAILURE);
	}
}

void	ft_parsing(t_data *data, int ac, char **av)
{
	ft_check_args(ac, av);
	ft_set_values(data, ac, av);
	ft_check_values(data);
}
