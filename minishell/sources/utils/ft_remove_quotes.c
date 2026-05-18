/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 03:41:40 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 04:23:24 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_quote_len(char *s)
{
	int		len;
	char	quote;

	len = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '"')
		{
			quote = *s++;
			while (*s && *s != quote && ++len)
				s++;
			if (*s)
				s++;
		}
		else if (++len)
			s++;
	}
	return (len);
}

char	*ft_remove_quotes(char *s)
{
	char	*res;
	int		i;
	int		j;
	char	quote;

	res = malloc(sizeof(char) * (ft_quote_len(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				res[j++] = s[i++];
			if (s[i])
				i++;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}
