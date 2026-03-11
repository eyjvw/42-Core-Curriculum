/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:45:07 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/18 22:18:42 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

int	main(int ac, char **av)
{
	t_all	all;

	ft_memset(&all, 0, sizeof(t_all));
	ft_check_and_init(&all, ac, av);
	ft_sort(&all);
	ft_clean_exit(&all, 0);
}
