/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:47:00 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/18 21:47:07 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	*ft_memset(void *s, int c, size_t x)
{
	size_t	i;

	i = 0;
	while (i < x)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}
