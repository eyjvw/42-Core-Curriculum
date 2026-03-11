/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:34:39 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/03 15:49:07 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int fd, int nb)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar_fd(fd, '-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(fd, n / 10);
	ft_putchar_fd(fd, n % 10 + '0');
}
