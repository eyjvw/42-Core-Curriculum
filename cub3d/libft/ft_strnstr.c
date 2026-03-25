/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:09:57 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/27 21:09:58 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*little)
		return ((char *)big);
	if (!*big)
		return (NULL);
	while (i < len && big[i + ft_strlen(little) - 1])
	{
		while ((i + j) < len && big[i + j] && big[i + j] == little[j])
		{
			if (little[++j] == 0)
				return (&((char *)big)[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
