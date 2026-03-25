/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublelen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 03:01:50 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/03 03:02:12 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_doublelen(char **strs)
{
	size_t	size;

	size = 0;
	if (!strs)
		return (size);
	while (strs[size])
		size++;
	return (size);
}
