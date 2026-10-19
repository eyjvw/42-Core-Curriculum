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

static int	ft_count_numbers(int ac, char **av)
{
	int		i;
	int		count;
	int		words;
	char	**split;

	count = 0;
	i = 1;
	while (i < ac)
	{
		split = ft_split(av[i], ' ');
		if (!split)
			return (0);
		words = 0;
		while (split[words])
			words++;
		ft_free_split(split, words);
		if (words == 0)
			return (0);
		count += words;
		i++;
	}
	return (count);
}

static void	ft_parse_arg(char *arg, int *numbers, int *n, t_all *all)
{
	int		i;
	int		count;
	char	**split;

	split = ft_split(arg, ' ');
	if (!split)
		return (ft_putstr_fd(2, "Error\n"), free(numbers),
			ft_clean_exit(all, 1));
	count = 0;
	while (split[count])
		count++;
	i = 0;
	while (split[i])
	{
		if (!ft_is_num(split[i]))
			return (ft_putstr_fd(2, "Error\n"), free(numbers),
				ft_free_split(split, count), ft_clean_exit(all, 1));
		numbers[*n] = ft_atoi(split[i], numbers);
		(*n)++;
		i++;
	}
	ft_free_split(split, count);
}

static void	ft_parsing(int ac, char **av, int *numbers, t_all *all)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (i < ac)
	{
		ft_parse_arg(av[i], numbers, &n, all);
		i++;
	}
}

void	ft_check_and_init(t_all *all, int ac, char **av)
{
	int	*numbers;
	int	size;

	if (ac < 2)
		ft_clean_exit(all, 0);
	size = ft_count_numbers(ac, av);
	if (size <= 0)
		return (ft_putstr_fd(2, "Error\n"), ft_clean_exit(all, 1));
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
