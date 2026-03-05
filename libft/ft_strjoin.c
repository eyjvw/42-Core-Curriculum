/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:11:25 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/05 03:42:25 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcat(char *dst, const char *src)
{
	size_t	i;

	i = ft_strlen(dst);
	while (*src)
		dst[i++] = *src++;
	dst[i] = '\0';
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!str)
		return (NULL);
	str[0] = '\0';
	ft_strcat(str, s1);
	ft_strcat(str, s2);
	return (str);
}
