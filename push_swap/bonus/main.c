/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 05:09:53 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 06:36:21 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	ft_is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->content > stack->next->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static void	ft_apply(char *line, t_all *all)
{
	if (!ft_strcmp(line, "sa\n"))
		sa(all);
	else if (!ft_strcmp(line, "sb\n"))
		sb(all);
	else if (!ft_strcmp(line, "ss\n"))
		ss(all);
	else if (!ft_strcmp(line, "pa\n"))
		pa(all);
	else if (!ft_strcmp(line, "pb\n"))
		pb(all);
	else if (!ft_strcmp(line, "ra\n"))
		ra(all);
	else if (!ft_strcmp(line, "rb\n"))
		rb(all);
	else if (!ft_strcmp(line, "rr\n"))
		rr(all);
	else if (!ft_strcmp(line, "rra\n"))
		rra(all);
	else if (!ft_strcmp(line, "rrb\n"))
		rrb(all);
	else if (!ft_strcmp(line, "rrr\n"))
		rrr(all);
	else
		return (ft_putstr_fd(2, "Error\n"), ft_clean_exit(all, 1));
}

int	main(int ac, char **av)
{
	t_all	all;
	char	*line;

	ft_memset(&all, 0, sizeof(t_all));
	ft_check_and_init(&all, ac, av);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		ft_apply(line, &all);
		free(line);
	}
	if (ft_is_sorted(all.a) == 1 && all.b == NULL)
		ft_putstr_fd(1, "OK\n");
	else
		ft_putstr_fd(1, "KO\n");
	ft_clean_exit(&all, 0);
}
