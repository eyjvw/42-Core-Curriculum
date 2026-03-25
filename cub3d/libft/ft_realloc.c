/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:45:01 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/11 17:45:11 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *old, size_t old_size, size_t new_size)
{
	size_t			smallest;
	unsigned char	*new;

	smallest = old_size;
	if (new_size < old_size)
		smallest = new_size;
	new = malloc(sizeof(char) * (new_size + 1));
	if (!new)
		return (free(old), NULL);
	return (ft_memcpy(new, old, smallest), free(old), new);
}
