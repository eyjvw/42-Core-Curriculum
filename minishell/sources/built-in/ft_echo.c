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
#include <stdio.h>

int	ft_echo(char **argv)
{
	int	i;
	int	n_flag;
	int	print_space;

	i = 1;
	n_flag = 0;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 2) && argv[i][2] == '\0')
	{
		n_flag = 1;
		i++;
	}
	print_space = 0;
	while (argv[i])
	{
		if (print_space)
			printf(" ");
		printf("%s", argv[i]);
		print_space = 1;
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
