/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:05:17 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/27 21:05:19 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*result;

	result = malloc(n * size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, (n * size));
	return (result);
}
