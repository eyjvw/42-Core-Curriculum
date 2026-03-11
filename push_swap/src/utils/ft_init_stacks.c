/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 04:29:14 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 05:57:28 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static t_stack	*ft_apply(t_all *all, t_stack *tail, t_stack *new_node)
{
	if (all->a == NULL)
	{
		all->a = new_node;
		return (new_node);
	}
	tail->next = new_node;
	return (new_node);
}

void	ft_init_stacks(t_all *all, int size, int *numbers)
{
	int		i;
	t_stack	*new_node;
	t_stack	*tail;

	all->a = NULL;
	all->b = NULL;
	tail = NULL;
	i = 0;
	while (i < size)
	{
		new_node = ft_create_stack(numbers[i]);
		if (!new_node)
			(ft_putstr_fd(2, "Error\n"), free(numbers),
				ft_clean_exit(all, 1));
		tail = ft_apply(all, tail, new_node);
		i++;
	}
}
