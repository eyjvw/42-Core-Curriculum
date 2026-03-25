/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:32:30 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/19 18:27:19 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strljoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = (ft_lento(s1, '\0') + ft_lento(s2, '\0') + 1);
	result = ft_calloc(sizeof(char), j);
	if (result == NULL)
		return (NULL);
	if (s1 != NULL)
	{
		while (s1[i])
		{
			result[i] = s1[i];
			i++;
		}
	}
	if (s2 != NULL)
	{
		j = 0;
		while (s2[j])
			result[i++] = s2[j++];
	}
	result[i] = '\0';
	return (result);
}

char	*join_and_free(char *s1_tofree, char *buffer)
{
	char	*result;

	result = ft_strljoin(s1_tofree, buffer);
	free(s1_tofree);
	return (result);
}

char	*kill_func(char *buffer, char **rest, int error)
{
	char	*line;

	line = NULL;
	if (error == 0 && *rest && **rest)
		line = ft_strljoin(*rest, buffer);
	if (buffer)
		free(buffer);
	if (*rest)
	{
		free(*rest);
		*rest = NULL;
	}
	return (line);
}

int	ft_lento(char *s, char c)
{
	int	len;

	if (!s || (!*s && *s == c))
		return (0);
	if (!*s && *s != c)
		return (-1);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (s[len] == c)
		return (len);
	return (-1);
}
