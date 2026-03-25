/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:11:03 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/27 21:11:05 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	find_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && is_set(s1[i], set))
		i++;
	return (i);
}

static size_t	find_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i >= 0 && is_set(s1[i], set))
		i--;
	if (i < 0)
		i = 0;
	return (i);
}

static char	*ft_moddeddup(char *dest, const char *s1, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	word_size;
	char	*result;

	if (!*s1)
		return (ft_substr(s1, 0, 0));
	start = find_start(s1, set);
	if (start == ft_strlen(s1))
		return (ft_substr(s1, 0, 0));
	end = find_end(s1, set);
	word_size = ((end - start) + 1);
	result = malloc(sizeof(char) * (word_size + 1));
	if (result == NULL)
		return (NULL);
	result = ft_moddeddup(result, &s1[start], word_size);
	return (result);
}
