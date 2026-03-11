/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_and_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:11:35 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/19 04:29:05 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_count_numbers(char *str)
{
	int		count;
	char	**split;

	split = ft_split(str, ' ');
	if (!split)
		return (0);
	count = 0;
	while (split[count])
		count++;
	ft_free_split(split, count);
	return (count);
}

static void	ft_one_av(char **av, int *numbers, t_all *all)
{
	int		i;
	char	**split;

	split = ft_split(av[1], ' ');
	if (!split)
		return (ft_putstr_fd(2, "Error\n"), ft_clean_exit(all, 1));
	i = 0;
	while (split[i])
	{
		if (!ft_is_num(split[i]))
			return (ft_putstr_fd(2, "Error\n"), free(numbers),
				ft_clean_exit(all, 1));
		numbers[i] = ft_atoi(split[i], numbers);
		i++;
	}
	ft_free_split(split, i);
}

static void	ft_multiple_av(int ac, char **av, int *numbers, t_all *all)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_is_num(av[i]))
			return (ft_putstr_fd(2, "Error\n"), free(numbers),
				ft_clean_exit(all, 1));
		numbers[i - 1] = ft_atoi(av[i], numbers);
		i++;
	}
}

static void	ft_parsing(int ac, char **av, int *numbers, t_all *all)
{
	if (ac == 2)
		ft_one_av(av, numbers, all);
	else
		ft_multiple_av(ac, av, numbers, all);
}

void	ft_check_and_init(t_all *all, int ac, char **av)
{
	int		*numbers;
	int		size;

	if (ac < 2)
		return (ft_putstr_fd(2, "Error\n"), ft_clean_exit(all, 1));
	if (ac == 2)
		size = ft_count_numbers(av[1]);
	else
		size = ac - 1;
	numbers = malloc(sizeof(int) * size);
	if (!numbers)
		return (ft_putstr_fd(2, "Error\n"), ft_clean_exit(all, 1));
	ft_parsing(ac, av, numbers, all);
	if (ft_has_dup(numbers, size))
		return (ft_putstr_fd(2, "Error\n"), free(numbers),
			ft_clean_exit(all, 1));
	ft_init_stacks(all, size, numbers);
	ft_init_index(all, size, numbers);
	free(numbers);
}
