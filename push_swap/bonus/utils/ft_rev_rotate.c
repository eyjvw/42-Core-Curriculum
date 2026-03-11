/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:58:15 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 06:35:28 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	rra(t_all *all)
{
	t_stack	*temp;
	t_stack	*last;

	if (!all || !all->a || !all->a->next)
		return ;
	temp = all->a;
	while (temp->next->next)
		temp = temp->next;
	last = temp->next;
	temp->next = NULL;
	last->next = all->a;
	all->a = last;
}

void	rrb(t_all *all)
{
	t_stack	*temp;
	t_stack	*last;

	if (!all || !all->b || !all->b->next)
		return ;
	temp = all->b;
	while (temp->next->next)
		temp = temp->next;
	last = temp->next;
	temp->next = NULL;
	last->next = all->b;
	all->b = last;
}

void	rrr(t_all *all)
{
	rra(all);
	rrb(all);
}
