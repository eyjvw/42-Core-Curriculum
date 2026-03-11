/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 05:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/05 05:08:28 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_uint_digits(unsigned int n)
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

static void	ft_write_uint_digits(char *res, int *i, unsigned int n)
{
	unsigned int	p;

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

char	*ft_uint_to_str(unsigned int n, t_flags flags)
{
	char	*res;
	int		i;
	int		digits;
	int		prec;

	res = malloc(BUFFER_SIZE);
	i = 0;
	digits = ft_count_uint_digits(n);
	prec = flags.precision;
	if (prec >= 0 && prec > digits)
	{
		while (prec-- > digits)
			res[i++] = '0';
	}
	if (!(flags.precision == 0 && n == 0))
		ft_write_uint_digits(res, &i, n);
	res[i] = 0;
	return (res);
}

int	ft_handle_conversion(va_list args, char c, int *i)
{
	int	count;

	count = 0;
	if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (c == 'u')
		count += ft_putunbr(va_arg(args, unsigned int));
	else if (c == 'x')
		count += ft_puthex(va_arg(args, unsigned int), 0);
	else if (c == 'X')
		count += ft_puthex(va_arg(args, unsigned int), 1);
	else if (c == 'p')
		count += ft_putptr(va_arg(args, void *));
	else if (c == '%')
		count += ft_putchar('%');
	(*i)++;
	return (count);
}
