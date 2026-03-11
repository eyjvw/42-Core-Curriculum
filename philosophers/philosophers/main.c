/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:30:12 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/30 13:30:10 by sbonneau         ###   ########.fr       */
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
