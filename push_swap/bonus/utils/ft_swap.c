/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:49:06 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 06:37:14 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	sa(t_all *all)
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
}

void	sb(t_all *all)
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
}

void	ss(t_all *all)
{
	sa(all);
	sb(all);
}
