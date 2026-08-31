/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:26:44 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 08:54:54 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** ft_check_args() has already rejected anything that is not a digit, so no
** sign is handled here. The overflow test is done before the multiplication,
** never after it, so the accumulator can never wrap around.
*/
static void	ft_overflow(void)
{
	ft_print_error(NULL, INVALID_ARGS);
	exit(EXIT_FAILURE);
}

int	ft_atoi(char *s)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	if (!s[0])
		ft_overflow();
	while (s[i])
	{
		if (num > (2147483647LL - (s[i] - '0')) / 10)
			ft_overflow();
		num = num * 10 + (s[i] - '0');
		i++;
	}
	return ((int)num);
}

long long	ft_atoll(char *s)
{
	unsigned long long	num;
	int					i;

	num = 0;
	i = 0;
	if (!s[0])
		ft_overflow();
	while (s[i])
	{
		if (num > (9223372036854775807ULL - (s[i] - '0')) / 10)
			ft_overflow();
		num = num * 10 + (s[i] - '0');
		i++;
	}
	return ((long long)num);
}
