/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chunk_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:12:15 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 04:15:42 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_chunk(t_all *all)
{
	int	chunk;
	int	i;

	i = 0;
	if (ft_size_stack(all->a) <= 100)
		chunk = 20;
	else
		chunk = 30;
	while (all->a)
	{
		if (all->a->index <= i)
		{
			ft_pb(all);
			ft_rb(all, 1);
			i++;
		}
		else if (all->a->index <= i + chunk)
		{
			ft_pb(all);
			i++;
		}
		else
			ft_ra(all, 1);
	}
}

void	ft_sort_to_a(t_all *all)
{
	int		index;
	int		pos;

	pos = 0;
	index = 0;
	while (ft_size_stack(all->b) > 0)
	{
		index = ft_max_index(all->b);
		pos = ft_index_pos(all->b, index);
		if (pos <= ft_size_stack(all->b) / 2)
		{
			while (all->b->index != index)
				ft_rb(all, 1);
		}
		else
		{
			while (all->b->index != index)
				ft_rrb(all, 1);
		}
		ft_pa(all);
	}
}
