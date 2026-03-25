/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:30:12 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:19:23 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	ft_parsing(&data, ac, av);
	ft_init(&data);
	ft_monitor(&data);
	ft_join(&data);
	ft_clean(&data);
	return (0);
}
