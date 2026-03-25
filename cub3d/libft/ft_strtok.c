/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:11:58 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/18 04:43:59 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*s;
	char		*ret;

	if (str)
		s = str;
	if (!s || !*s)
		return (NULL);
	ret = s;
	while (*s && ft_isset(*s, delim))
	{
		s++;
		ret++;
	}
	while (*s && !ft_isset(*s, delim))
		s++;
	if (*s && ft_isset(*s, delim))
		*(s++) = 0;
	return (ret);
}
