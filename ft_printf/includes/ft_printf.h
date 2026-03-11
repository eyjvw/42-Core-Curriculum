/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:24:31 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 05:13:19 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

typedef struct s_flags
{
	int	minus;
	int	zero;
	int	hash;
	int	plus;
	int	space;
	int	width;
	int	precision;
}	t_flags;

int		ft_printf(const char *format, ...);
int		ft_putchar(int c);
int		ft_putnbr(int n);
int		ft_putstr(char *s);
int		ft_putunbr(unsigned int n);
int		ft_putptr(void *ptr);
int		ft_puthex(unsigned int n, int upper);
int		ft_strlen_custom(const char *s);
int		ft_is_flag_or_digit(char c);
int		ft_print_left_pad(int len, int width);
int		ft_print_right_pad(int len, int width);
int		ft_handle_conversion(va_list args, char c, int *i);
int		ft_print_char_with_flags(int c, t_flags flags);
int		ft_print_str_with_flags(char *s, t_flags flags);
int		ft_print_ptr_with_flags(void *ptr, t_flags flags);

char	*ft_int_to_str(long n, t_flags flags);
char	*ft_uint_to_str(unsigned int n, t_flags flags);
char	*ft_hex_to_str(unsigned long n, int upper, t_flags flags);
char	*ft_get_conversion(va_list args, char c, t_flags flags);

t_flags	ft_parse_flags(const char *format, int *i);

