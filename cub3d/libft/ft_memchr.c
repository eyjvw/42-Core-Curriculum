/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:09:34 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/27 21:09:35 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	ch;
	unsigned char	*area;

	i = 0;
	ch = c;
	area = (unsigned char *)s;
	while (i < n)
	{
		if (area[i] == ch)
			return (&area[i]);
		i++;
	}
	return (NULL);
}
