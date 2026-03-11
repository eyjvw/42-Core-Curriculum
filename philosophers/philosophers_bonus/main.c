/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:30:12 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/02 05:26:40 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	ft_parsing(&data, ac, av);
	ft_init(&data);
	ft_fork(&data);
	ft_wait(&data);
	ft_clean(&data, true);
	return (0);
}
