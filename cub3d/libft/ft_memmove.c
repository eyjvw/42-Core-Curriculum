/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:07:41 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/27 21:07:42 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*area;
	const unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	i = 0;
	area = dest;
	source = src;
	if (src < dest)
	{
		while (n-- > 0)
			area[n] = source[n];
	}
	else
	{
		while (i < n)
		{
			area[i] = source[i];
			i++;
		}
	}
	return (dest);
}
