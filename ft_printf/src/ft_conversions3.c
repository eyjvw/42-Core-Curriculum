/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/05 05:08:28 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_add_prefix(char *res, int *i, t_flags flags, unsigned long n)
{
	if (flags.hash && n != 0)
	{
		res[(*i)++] = '0';
		if (flags.hash == 2)
			res[(*i)++] = 'X';
		else
			res[(*i)++] = 'x';
	}
}

static int	ft_count_hex_digits(unsigned long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

static void	ft_write_hex(char *res, int *i, unsigned long n, const char *h)
{
	unsigned long	p;

	p = 1;
	while (p <= n / 16)
		p *= 16;
	while (p > 0)
	{
		res[(*i)++] = h[n / p];
		n %= p;
		p /= 16;
	}
}

static void	ft_apply_hex_prec(char *res, int *i, int digits, int prec)
{
	if (prec >= 0 && prec > digits)
	{
		while (prec-- > digits)
			res[(*i)++] = '0';
	}
}

char	*ft_hex_to_str(unsigned long n, int upper, t_flags flags)
{
	const char	*hex;
	char		*res;
	int			i;
	t_flags		temp_flags;

	if (upper)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	res = malloc(BUFFER_SIZE);
	i = 0;
	temp_flags = flags;
	if (upper && flags.hash)
		temp_flags.hash = 2;
	if (!(flags.precision == 0 && n == 0))
		ft_add_prefix(res, &i, temp_flags, n);
	ft_apply_hex_prec(res, &i, ft_count_hex_digits(n), flags.precision);
	if (!(flags.precision == 0 && n == 0))
		ft_write_hex(res, &i, n, hex);
	res[i] = 0;
	return (res);
}
