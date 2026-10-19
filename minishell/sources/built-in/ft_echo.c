/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:47:56 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 04:00:49 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_is_n_flag(char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	ft_echo(char **argv)
{
	int	i;
	int	n_flag;
	int	print_space;

	i = 1;
	n_flag = 0;
	while (argv[i] && ft_is_n_flag(argv[i]))
	{
		n_flag = 1;
		i++;
	}
	print_space = 0;
	while (argv[i])
	{
		if (print_space)
			ft_putstr_fd(STDOUT_FILENO, " ");
		ft_putstr_fd(STDOUT_FILENO, argv[i]);
		print_space = 1;
		i++;
	}
	if (!n_flag)
		ft_putstr_fd(STDOUT_FILENO, "\n");
	return (0);
}
