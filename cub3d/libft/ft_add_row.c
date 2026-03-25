/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_row.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 03:07:18 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/11 20:57:11 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_row(char *new_row, char **strs)
{
	int	size;

	size = ft_doublelen(strs);
	strs = ft_double_realloc(strs, size, size + 2);
	if (!strs)
		return (NULL);
	strs[size] = new_row;
	strs[size + 1] = NULL;
	return (strs);
}
