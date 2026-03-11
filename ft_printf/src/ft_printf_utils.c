/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:45:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/05 05:08:28 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen_custom(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_is_flag_or_digit(char c)
{
	return (c == '-' || c == '0' || c == '+'
		|| c == ' ' || c == '#' || c == '.' || (c >= '0' && c <= '9'));
}

int	ft_print_left_pad(int len, int width)
{
	int	count;

	count = 0;
	while (count < width - len)
	{
		write(1, " ", 1);
		count++;
	}
	return (count);
}

int	ft_print_right_pad(int len, int width)
{
	int	pad;
	int	count;

	count = 0;
	pad = width - len;
	while (pad-- > 0)
		count += write(1, " ", 1);
	return (count);
}

char	*ft_get_conversion(va_list args, char c, t_flags flags)
{
	if (c == 'd' || c == 'i')
		return (ft_int_to_str((long)va_arg(args, int), flags));
	else if (c == 'u')
		return (ft_uint_to_str(va_arg(args, unsigned int), flags));
	else if (c == 'x' || c == 'X')
		return (ft_hex_to_str((unsigned long)va_arg(args, unsigned int),
				c == 'X', flags));
	return (NULL);
}
