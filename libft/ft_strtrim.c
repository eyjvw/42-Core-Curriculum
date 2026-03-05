/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 23:30:53 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/05 03:41:57 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i])
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(const char *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	size_t	i;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	start = 0;
	while (start < len && ft_is_in_set(s1[start], set))
		start++;
	end = len;
	while (end > start && ft_is_in_set(s1[end - 1], set))
		end--;
	res = (char *)malloc((end - start) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (start < end)
		res[i++] = s1[start++];
	res[i] = '\0';
	return (res);
}
