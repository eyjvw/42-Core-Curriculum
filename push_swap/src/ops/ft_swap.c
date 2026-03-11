/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:49:06 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/18 23:00:08 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sa(t_all *all, int print)
{
	t_stack	*first;
	t_stack	*second;

	if (!all || !all->a || !all->a->next)
		return ;
	first = all->a;
	second = first->next;
	first->next = second->next;
	second->next = first;
	all->a = second;
	if (print)
		ft_putstr_fd(1, "sa\n");
}

void	ft_sb(t_all *all, int print)
{
	t_stack	*first;
	t_stack	*second;

	if (!all || !all->b || !all->b->next)
		return ;
	first = all->b;
	second = first->next;
	first->next = second->next;
	second->next = first;
	all->b = second;
	if (print)
		ft_putstr_fd(1, "sb\n");
}

void	ft_ss(t_all *all)
{
	ft_sa(all, 0);
	ft_sb(all, 0);
	ft_putstr_fd(1, "ss\n");
}
