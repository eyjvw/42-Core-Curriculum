/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:06:27 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 02:08:27 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_numbers_swap(int size, int *numbers)
{
	int	swap;
	int	j;
	int	i;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (numbers[i] > numbers[j])
			{
				swap = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = swap;
			}
			j++;
		}
		i++;
	}
}

static void	ft_set_index(t_stack *stack, int size, int *numbers)
{
	int		i;
	t_stack	*temp;

	temp = stack;
	while (temp)
	{
		i = 0;
		while (i < size)
		{
			if (temp->content == numbers[i])
			{
				temp->index = i;
				break ;
			}
			i++;
		}
		temp = temp->next;
	}
}

void	ft_init_index(t_all *all, int size, int *numbers)
{
	ft_numbers_swap(size, numbers);
	ft_set_index(all->a, size, numbers);
}
