/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:58:15 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 03:04:13 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_rra(t_all *all, int print)
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
	if (print)
		ft_putstr_fd(1, "rra\n");
}

void	ft_rrb(t_all *all, int print)
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
	if (print)
		ft_putstr_fd(1, "rrb\n");
}

void	ft_rrr(t_all *all)
{
	ft_rra(all, 0);
	ft_rrb(all, 0);
	ft_putstr_fd(1, "rrr\n");
}
