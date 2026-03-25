/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:07:31 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/27 21:07:32 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*area;
	const unsigned char	*source;

	if (!dest && !src)
		return (NULL);
	i = 0;
	area = dest;
	source = src;
	while (i < n)
	{
		area[i] = source[i];
		i++;
	}
	return (dest);
}
