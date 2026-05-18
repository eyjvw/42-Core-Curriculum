/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 02:22:08 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/08 03:47:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_match(char *pattern, char *str)
{
	if (!pattern || !str)
		return (false);
	while (*pattern && *str)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (!*pattern)
				return (true);
			while (*str)
			{
				if (ft_match(pattern, str))
					return (true);
				str++;
			}
			return (false);
		}
		if (*pattern != *str)
			return (false);
		pattern++;
		str++;
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern && !*str);
}

t_tokens	*ft_expand_wildcards(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_tokens		*tokens;

	tokens = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (!(pattern[0] != '.' && entry->d_name[0] == '.'))
		{
			if (ft_match(pattern, entry->d_name))
				ft_lst_addback((void **)&tokens,
					ft_create_token(ft_strdup(entry->d_name), WORD));
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (tokens);
}
