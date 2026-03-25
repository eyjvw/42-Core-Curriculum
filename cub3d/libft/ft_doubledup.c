/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubledup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 03:04:43 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/18 04:21:00 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_doubledup(char **srcs)
{
	int		i;
	size_t	size;
	char	**res;

	i = -1;
	size = ft_doublelen(srcs);
	res = malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		return (NULL);
	while (++i < (int)size)
	{
		res[i] = ft_strdup(srcs[i]);
		if (res[i] == NULL)
			return (ft_double_free(res), NULL);
	}
	res[i] = NULL;
	return (res);
}
