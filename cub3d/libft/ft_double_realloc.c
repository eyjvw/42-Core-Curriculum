/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 03:15:08 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/03 03:17:27 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_double_realloc(char **old, size_t old_ptr_n, size_t new_ptr_n)
{
	size_t		i;
	char		**new;

	i = 0;
	new = malloc(sizeof(char *) * (new_ptr_n + 1));
	if (!new)
		return (ft_double_free(old), NULL);
	while (i < new_ptr_n && i < old_ptr_n)
	{
		new[i] = old[i];
		i++;
	}
	while (i <= new_ptr_n)
		new[i++] = NULL;
	free(old);
	return (new);
}
