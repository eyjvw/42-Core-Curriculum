/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 05:30:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/05 05:08:28 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char_with_flags(int c, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.width > 1 && !flags.minus)
		count += ft_print_left_pad(1, flags.width);
	count += ft_putchar(c);
	if (flags.width > 1 && flags.minus)
		count += ft_print_right_pad(1, flags.width);
	return (count);
}

static int	ft_get_str_len(char *s, t_flags flags)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	if (flags.precision >= 0 && flags.precision < len)
		return (flags.precision);
	return (len);
}

int	ft_print_str_with_flags(char *s, t_flags flags)
{
	int	count;
	int	len;

	count = 0;
	if (!s)
		s = "(null)";
	len = ft_get_str_len(s, flags);
	if (flags.width > len && !flags.minus)
		count += ft_print_left_pad(len, flags.width);
	count += write(1, s, len);
	if (flags.width > len && flags.minus)
		count += ft_print_right_pad(len, flags.width);
	return (count);
}

static int	ft_get_ptr_len(unsigned long ptr)
{
	int	len;

	if (!ptr)
		return (5);
	len = 2;
	while (ptr > 0)
	{
		ptr /= 16;
		len++;
	}
	return (len);
}

int	ft_print_ptr_with_flags(void *ptr, t_flags flags)
{
	int	count;
	int	len;

	count = 0;
	len = ft_get_ptr_len((unsigned long)ptr);
	if (flags.width > len && !flags.minus)
		count += ft_print_left_pad(len, flags.width);
	count += ft_putptr(ptr);
	if (flags.width > len && flags.minus)
		count += ft_print_right_pad(len, flags.width);
	return (count);
}
