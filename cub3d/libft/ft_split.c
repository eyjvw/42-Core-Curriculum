/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 03:27:46 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/12 03:28:46 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strndup(const char *s, ssize_t len)
{
	ssize_t	i;
	char	*res;

	i = -1;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (s[++i] && i < len)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

static	bool	is_sep(char c, const char *sep)
{
	while (*sep && *sep != c)
		sep++;
	return (c == *sep);
}

static	size_t	len_to_sep(const char *str, const char *sep)
{
	size_t	i;

	i = 0;
	while (str[i] && !is_sep(str[i], sep))
		i++;
	return (i);
}

char	**ft_split(const char *str, const char *sep)
{
	size_t	size;
	char	**result;

	if (!str || !*str || !sep || !*sep)
		return (NULL);
	size = 0;
	result = malloc(sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = NULL;
	while (*str)
	{
		while (*str && is_sep(*str, sep))
			str++;
		if (!*str)
			return (result);
		result = ft_double_realloc(result, size, size + 1);
		result[size] = ft_strndup(str, len_to_sep(str, sep));
		if (!result[size])
			return (ft_double_free(result), NULL);
		str += len_to_sep(str, sep);
		size++;
	}
	return (result);
}
