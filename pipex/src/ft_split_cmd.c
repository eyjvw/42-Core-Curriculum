/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/10/19 15:00:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_is_sep(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	ft_is_escape(char *s, int i, char quote)
{
	if (s[i] != '\\' || !s[i + 1] || quote == '\'')
		return (0);
	if (!quote)
		return (1);
	return (s[i + 1] == '"' || s[i + 1] == '\\' || s[i + 1] == '$'
		|| s[i + 1] == '`');
}

static int	ft_scan(char *s, int *i, char *dst)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (s[*i] && (quote || !ft_is_sep(s[*i])))
	{
		if (!quote && (s[*i] == '\'' || s[*i] == '"'))
			quote = s[*i];
		else if (quote && s[*i] == quote)
			quote = 0;
		else
		{
			if (ft_is_escape(s, *i, quote))
				(*i)++;
			if (dst)
				dst[len] = s[*i];
			len++;
		}
		(*i)++;
	}
	return (len);
}

static int	ft_count_args(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_is_sep(s[i]))
			i++;
		if (!s[i])
			break ;
		ft_scan(s, &i, NULL);
		count++;
	}
	return (count);
}

char	**ft_split_cmd(char *s)
{
	char	**result;
	int		count;
	int		i;
	int		j;
	int		start;

	count = ft_count_args(s);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < count)
	{
		while (ft_is_sep(s[i]))
			i++;
		start = i;
		result[j] = malloc(ft_scan(s, &i, NULL) + 1);
		if (!result[j])
			return (ft_free_split(result, j), NULL);
		i = start;
		result[j][ft_scan(s, &i, result[j])] = '\0';
	}
	result[j] = NULL;
	return (result);
}
