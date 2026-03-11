/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 03:26:59 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 04:06:01 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	ft_max_index(t_stack *stack)
{
	int	index_max;

	if (!stack)
		return (-1);
	index_max = stack->index;
	while (stack)
	{
		if (stack->index > index_max)
		{
			index_max = stack->index;
		}
		stack = stack->next;
	}
	return (index_max);
}

int	ft_index_pos(t_stack *stack, int index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		stack = stack->next;
		pos++;
	}
	return (-1);
}

int	ft_min_index(t_stack *stack)
{
	int		index;
	int		min_index;
	int		min_value;
	t_stack	*temp;

	if (!stack)
		return (-1);
	index = 0;
	min_index = 0;
	temp = stack;
	min_value = temp->index;
	while (temp)
	{
		if (temp->index < min_value)
		{
			min_value = temp->index;
			min_index = index;
		}
		temp = temp->next;
		index++;
	}
	return (min_index);
}
