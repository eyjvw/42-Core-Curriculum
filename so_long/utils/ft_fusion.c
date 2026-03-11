/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 05:50:00 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/11 05:53:15 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static size_t	ft_intlen(int n)
{
	size_t	len;

	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static size_t	ft_copy_str(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

static void	ft_create_buffer(char *d, long nb, size_t *n)
{
	char	buffer[20];
	size_t	j;

	j = 0;
	while (nb > 0)
	{
		buffer[j++] = (nb % 10) + '0';
		nb /= 10;
	}
	while (j > 0)
		d[(*n)++] = buffer[--j];
}

char	*ft_fusion(const char *str, int n)
{
	size_t	str_len;
	size_t	int_len;
	size_t	i;
	char	*res;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	int_len = ft_intlen(n);
	res = malloc(str_len + int_len + 1);
	if (!res)
		return (NULL);
	i = ft_copy_str(res, str);
	if (n == 0)
		res[i++] = '0';
	else
		ft_create_buffer(res, n, &i);
	res[i] = '\0';
	return (res);
}
