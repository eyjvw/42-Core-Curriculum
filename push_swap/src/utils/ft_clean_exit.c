/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:48:22 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 03:07:52 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	ft_clean_node(t_stack *stack)
{
	t_stack	*temp;

	while (stack)
	{
		temp = stack->next;
		free(stack);
		stack = temp;
	}
}

void	ft_clean_exit(t_all *all, int code)
{
	if (all)
	{
		if (all->a)
			(ft_clean_node(all->a), all->a = NULL);
		if (all->b)
			(ft_clean_node(all->b), all->b = NULL);
	}
	exit(code);
}
