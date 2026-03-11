/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:54:41 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 03:04:31 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_ra(t_all *all, int print)
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
	if (print)
		ft_putstr_fd(1, "ra\n");
}

void	ft_rb(t_all *all, int print)
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
	if (print)
		ft_putstr_fd(1, "rb\n");
}

void	ft_rr(t_all *all)
{
	ft_ra(all, 0);
	ft_rb(all, 0);
	ft_putstr_fd(1, "rr\n");
}
