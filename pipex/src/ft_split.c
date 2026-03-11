/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:38:07 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/20 03:45:53 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	ft_word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static void	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}

void	ft_free_split(char **split, int index)
{
	int	i;

	if (index == -1)
	{
		i = 0;
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	else
	{
		while (index > 0)
		{
			free(split[index - 1]);
			index--;
		}
	}
	free(split);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	int		word_count;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (*s && *s == c)
			s++;
		len = ft_word_len(s, c);
		result[i] = malloc(sizeof(char) * (len + 1));
		if (!result[i])
			return (ft_free_split(result, i), NULL);
		ft_strlcpy(result[i], s, len + 1);
		s += len;
		i++;
	}
	return (result[i] = NULL, result);
}
