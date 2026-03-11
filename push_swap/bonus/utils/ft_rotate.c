/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:54:41 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 06:35:41 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_all *all)
{
	t_stack	*first;
	t_stack	*last;

	if (!all || !all->a || !all->a->next)
		return ;
	first = all->a;
	all->a = first->next;
	last = all->a;
	while (last && last->next)
		last = last->next;
	if (last)
	{
		last->next = first;
		first->next = NULL;
	}
}

void	rb(t_all *all)
{
	t_stack	*first;
	t_stack	*last;

	if (!all || !all->b || !all->b->next)
		return ;
	first = all->b;
	all->b = first->next;
	last = all->b;
	while (last->next)
		last = last->next;
	if (last)
	{
		last->next = first;
		first->next = NULL;
	}
}

void	rr(t_all *all)
{
	ra(all);
	rb(all);
}
