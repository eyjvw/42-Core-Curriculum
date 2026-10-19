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
	if (*pattern == '*')
	{
		while (pattern[1] == '*')
			pattern++;
		if (ft_match(pattern + 1, str))
			return (true);
		return (*str && ft_match(pattern, str + 1));
	}
	if (!*pattern || !*str)
		return (!*pattern && !*str);
	if (*pattern == *str || (*pattern == STAR_MARK && *str == '*'))
		return (ft_match(pattern + 1, str + 1));
	return (false);
}

static void	ft_insert_sorted(t_tokens **list, char *name)
{
	t_tokens	*new;
	t_tokens	**curr;

	new = ft_create_token(name, WORD);
	if (!new)
		return ;
	curr = list;
	while (*curr && ft_strcmp((*curr)->value, name) < 0)
		curr = &(*curr)->next;
	new->next = *curr;
	*curr = new;
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
		if ((pattern[0] == '.' || entry->d_name[0] != '.')
			&& ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, "..")
			&& ft_match(pattern, entry->d_name))
			ft_insert_sorted(&tokens, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (tokens);
}
