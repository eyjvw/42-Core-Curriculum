/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_medium_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 03:25:18 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 04:06:25 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_medium_sort(t_all *all)
{
	int	size;
	int	min_index;

	while (ft_size_stack(all->a) > 3)
	{
		min_index = ft_min_index(all->a);
		size = ft_size_stack(all->a);
		if (min_index <= size / 2)
		{
			while (min_index > 0)
				(ft_ra(all, 1), min_index--);
		}
		else
		{
			while (min_index < size)
				(ft_rra(all, 1), min_index++);
		}
		ft_pb(all);
	}
	ft_three_sort(all);
	while (ft_size_stack(all->b) > 0)
		ft_pa(all);
}
