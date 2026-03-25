/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_row.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 03:07:40 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/11 20:57:46 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_delete_row(size_t id, char **strs)
{
	int		i;
	int		j;
	int		size;
	char	**res;

	i = 0;
	j = 0;
	size = ft_doublelen(strs);
	res = malloc(sizeof(char *) * size);
	if (!res)
		return (NULL);
	while (j < size && strs[j])
	{
		if (i == (int)id)
			j++;
		res[i++] = strs[j++];
	}
	res[i] = NULL;
	free(strs[id]);
	free(strs);
	strs = res;
	return (strs);
}
