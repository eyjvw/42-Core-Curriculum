/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 02:11:12 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/05 04:43:08 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex_base(unsigned long n, const char *base)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_puthex_base(n / 16, base);
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_puthex(unsigned int n, int upper)
{
	const char	*base;

	if (upper == 1)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	return (ft_puthex_base((unsigned long)n, base));
}

int	ft_putptr(void *ptr)
{
	int	count;

	if (!ptr)
		return (ft_putstr("(nil)"));
	count = 0;
	count += ft_putstr("0x");
	count += ft_puthex_base((unsigned long)ptr, "0123456789abcdef");
	return (count);
}

/*
** Allocates a conversion buffer big enough for the longest possible result:
** the digits themselves or the requested precision, whichever is larger, plus
** room for a sign or an 0x prefix and the terminating NUL.
*/
char	*ft_alloc_num(int digits, int precision)
{
	int	size;

	size = digits;
	if (precision > size)
		size = precision;
	return (malloc(size + 4));
}
