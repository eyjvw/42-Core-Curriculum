/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:10:45 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/27 21:10:45 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s) || !*s)
	{
		result = malloc(1);
		if (result == NULL)
			return (NULL);
		result[0] = 0;
		return (result);
	}
	if (ft_strlen(&s[start]) < len)
		result = malloc(sizeof(char) * (ft_strlen(&s[start]) + 1));
	else
		result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start])
		result[i++] = s[start++];
	result[i] = '\0';
	return (result);
}
