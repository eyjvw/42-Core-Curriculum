/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:18:46 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 04:15:47 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	ft_is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->content > stack->next->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	ft_sort(t_all *all)
{
	int	size;

	if (ft_is_sorted(all->a))
		return ;
	size = ft_size_stack(all->a);
	if (size <= 3)
		return (ft_three_sort(all));
	else if (size == 4 || size == 5)
		return (ft_medium_sort(all));
	else
		return (ft_chunk(all), ft_sort_to_a(all));
}
