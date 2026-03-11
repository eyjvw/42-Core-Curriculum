/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:26:44 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/01 22:49:04 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *s)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	if (s[0] == '-' || s[0] == '+')
	{
		if (s[0] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		num = num * 10 + (s[i] - '0');
		if (sign == 1 && num > 2147483647)
			return (ft_print_error(NULL, INVALID_ARGS), exit(EXIT_FAILURE), 0);
		if (sign == -1 && num > 2147483648)
			return (ft_print_error(NULL, INVALID_ARGS), exit(EXIT_FAILURE), 0);
		i++;
	}
	return ((int)(num * sign));
}

long long	ft_atoll(char *s)
{
	unsigned long long	num;
	int					sign;
	int					i;

	num = 0;
	sign = 1;
	i = 0;
	if (s[0] == '-' || s[0] == '+')
	{
		if (s[0] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		num = num * 10 + (s[i] - '0');
		if (sign == 1 && num > 9223372036854775807LL)
			return (ft_print_error(NULL, INVALID_ARGS), exit(EXIT_FAILURE), 0);
		if (sign == -1 && (unsigned long long)num > 9223372036854775808ULL)
			return (ft_print_error(NULL, INVALID_ARGS), exit(EXIT_FAILURE), 0);
		i++;
	}
	return (num * sign);
}
