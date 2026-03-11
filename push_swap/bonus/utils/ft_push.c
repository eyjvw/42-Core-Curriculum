/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:46:47 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 06:35:15 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_all *all)
{
	t_stack	*temp;

	if (!all || !all->b)
		return ;
	temp = all->b;
	all->b = all->b->next;
	temp->next = all->a;
	all->a = temp;
}

void	pb(t_all *all)
{
	t_stack	*temp;

	if (!all || !all->a)
		return ;
	temp = all->a;
	all->a = all->a->next;
	temp->next = all->b;
	all->b = temp;
}
