/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:23:10 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/05 05:08:28 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Zero padding goes after whatever must stay glued to the left of the number:
** a sign for %d, or the 0x / 0X prefix added by the # flag. Padding in front
** of it would print 00000xff instead of 0x0000ff.
*/
static int	ft_handle_zero_pad(char *str, int len, int pad_count)
{
	int	count;
	int	i;
	int	skip;

	count = 0;
	i = 0;
	skip = 0;
	if (str[0] == '+' || str[0] == '-' || str[0] == ' ')
		skip = 1;
	else if (len > 1 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		skip = 2;
	if (skip > 0)
		count += write(1, str, skip);
	while (i < pad_count)
	{
		write(1, "0", 1);
		i++;
	}
	count += pad_count;
	count += write(1, str + skip, len - skip);
	return (count);
}

static int	ft_print_with_padding(char *str, int len, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.width > len && !flags.minus)
	{
		if (flags.zero)
			count += ft_handle_zero_pad(str, len, flags.width - len);
		else
		{
			count += ft_print_left_pad(len, flags.width);
			count += write(1, str, len);
		}
	}
	else
	{
		count += write(1, str, len);
		if (flags.width > len && flags.minus)
			count += ft_print_right_pad(len, flags.width);
	}
	return (count);
}

static int	ft_process_format(va_list args, const char *fmt, int *idx)
{
	t_flags	flags;
	char	*str;
	char	c;
	int		len;
	int		count;

	flags = ft_parse_flags(fmt, idx);
	if (flags.precision >= 0)
		flags.zero = 0;
	c = fmt[*idx];
	if (c == 'c')
		return (ft_print_char_with_flags(va_arg(args, int), flags));
	else if (c == 's')
		return (ft_print_str_with_flags(va_arg(args, char *), flags));
	else if (c == 'p')
		return (ft_print_ptr_with_flags(va_arg(args, void *), flags));
	else if (c == '%')
		return (ft_print_char_with_flags('%', flags));
	str = ft_get_conversion(args, c, flags);
	if (!str)
		return (0);
	len = ft_strlen_custom(str);
	count = ft_print_with_padding(str, len, flags);
	free(str);
	return (count);
}

static int	ft_process_one_char(va_list args, const char *format, int *i)
{
	int	count;

	count = 0;
	if (format[*i] == '%' && format[*i + 1])
	{
		(*i)++;
		if (ft_is_flag_or_digit(format[*i]))
		{
			count += ft_process_format(args, format, i);
			(*i)++;
		}
		else
			count += ft_handle_conversion(args, format[*i], i);
	}
	else
	{
		count += ft_putchar(format[*i]);
		(*i)++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!format)
		return (0);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
		count += ft_process_one_char(args, format, &i);
	va_end(args);
	return (count);
}
