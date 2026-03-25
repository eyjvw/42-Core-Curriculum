/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:09:15 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/27 21:09:16 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	ch;

	ch = c;
	i = ft_strlen(s);
	if (s[i] == ch)
		return ((char *)(s + i));
	while (i > 0)
	{
		i--;
		if (s[i] == ch)
			return ((char *)(s + i));
	}
	return (NULL);
}
