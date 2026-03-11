/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 00:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/05 04:43:08 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_is_flag_char(char c)
{
	return (c == '-' || c == '0' || c == '#' || c == '+' || c == ' ');
}

static void	ft_init_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->hash = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->width = 0;
	flags->precision = -1;
}

static void	ft_parse_flag_chars(const char *format, int *i, t_flags *flags)
{
	while (format[*i] && ft_is_flag_char(format[*i]))
	{
		if (format[*i] == '-')
			flags->minus = 1;
		else if (format[*i] == '0' && !flags->minus)
			flags->zero = 1;
		else if (format[*i] == '#')
			flags->hash = 1;
		else if (format[*i] == '+')
			flags->plus = 1;
		else if (format[*i] == ' ' && !flags->plus)
			flags->space = 1;
		(*i)++;
	}
}

t_flags	ft_parse_flags(const char *format, int *i)
{
	t_flags	flags;

	ft_init_flags(&flags);
	ft_parse_flag_chars(format, i, &flags);
	while (format[*i] >= '0' && format[*i] <= '9')
	{
		flags.width = flags.width * 10 + (format[*i] - '0');
		(*i)++;
	}
	if (format[*i] == '.')
	{
		flags.precision = 0;
		(*i)++;
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			flags.precision = flags.precision * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
	return (flags);
}
