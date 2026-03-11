/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:46:47 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 03:03:48 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_pa(t_all *all)
{
	t_stack	*temp;

	if (!all || !all->b)
		return ;
	temp = all->b;
	all->b = all->b->next;
	temp->next = all->a;
	all->a = temp;
	ft_putstr_fd(1, "pa\n");
}

void	ft_pb(t_all *all)
{
	t_stack	*temp;

	if (!all || !all->a)
		return ;
	temp = all->a;
	all->a = all->a->next;
	temp->next = all->b;
	all->b = temp;
	ft_putstr_fd(1, "pb\n");
}
