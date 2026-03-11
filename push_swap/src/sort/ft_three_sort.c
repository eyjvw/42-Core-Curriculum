/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_three_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:45:25 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/18 23:04:59 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_three_sort(t_all *all)
{
	int	a;
	int	b;
	int	c;

	if (all->a == NULL || all->a->next == NULL)
		return ;
	if (all->a->next->next == NULL)
	{
		if (all->a->content > all->a->next->content)
			ft_sa(all, 1);
		return ;
	}
	a = all->a->content;
	b = all->a->next->content;
	c = all->a->next->next->content;
	if (a > b && a < c && b < c)
		ft_sa(all, 1);
	else if (a > b && a > c && b < c)
		ft_ra(all, 1);
	else if (a < b && a > c && b > c)
		ft_rra(all, 1);
	else if (a > b && a > c && b > c)
		(ft_sa(all, 1), ft_rra(all, 1));
	else if (a < b && a < c && b > c)
		(ft_sa(all, 1), ft_ra(all, 1));
}
