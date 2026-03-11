/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:35:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/05 05:08:28 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_sign(char *res, int *i, long *n, t_flags flags)
{
	if (*n < 0)
	{
		res[(*i)++] = '-';
		*n = -*n;
	}
	else if (flags.plus)
		res[(*i)++] = '+';
	else if (flags.space)
		res[(*i)++] = ' ';
}

static int	ft_count_digits(long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_write_digits(char *res, int *i, long n)
{
	long	p;

	p = 1;
	while (p <= n / 10)
		p *= 10;
	while (p > 0)
	{
		res[(*i)++] = (n / p) + '0';
		n %= p;
		p /= 10;
	}
}

char	*ft_int_to_str(long n, t_flags flags)
{
	char	*res;
	int		i;
	int		digits;
	int		prec;

	res = malloc(BUFFER_SIZE);
	i = 0;
	ft_put_sign(res, &i, &n, flags);
	digits = ft_count_digits(n);
	prec = flags.precision;
	if (prec >= 0 && prec > digits)
	{
		while (prec-- > digits)
			res[i++] = '0';
	}
	if (!(flags.precision == 0 && n == 0))
		ft_write_digits(res, &i, n);
	res[i] = 0;
	return (res);
}
