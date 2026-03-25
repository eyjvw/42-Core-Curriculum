/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmaxlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:25:35 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/10 17:30:03 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strmaxlen(char **strs)
{
	size_t	i;
	size_t	j;
	size_t	max;

	i = 0;
	j = 0;
	max = 0;
	while (strs[j])
	{
		while (strs[j][i])
			i++;
		if (i > max)
			max = i;
		i = 0;
		j++;
	}
	return (max);
}
