/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	ft_word_end(char *s, int i)
{
	bool	quoted;

	quoted = false;
	while (s[i] && (quoted || !ft_is_ifs(s[i])))
	{
		if (s[i] == QUOTE_MARK)
			quoted = !quoted;
		i++;
	}
	return (i);
}

t_tokens	*ft_split_words(char *s)
{
	t_tokens	*list;
	char		*word;
	int			end;
	int			i;

	list = NULL;
	i = 0;
	while (s[i])
	{
		end = ft_word_end(s, i);
		if (end == i)
		{
			i++;
			continue ;
		}
		word = ft_substr(s, i, end - i);
		ft_lst_addback((void **)&list, ft_create_token(word, WORD));
		free(word);
		i = end;
	}
	return (list);
}

bool	ft_has_glob(char *s)
{
	bool	quoted;

	quoted = false;
	while (*s)
	{
		if (*s == QUOTE_MARK)
			quoted = !quoted;
		else if (*s == '*' && !quoted)
			return (true);
		s++;
	}
	return (false);
}

char	*ft_unmark(char *s, bool glob)
{
	char	*res;
	bool	quoted;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	quoted = false;
	i = 0;
	while (*s)
	{
		if (*s == QUOTE_MARK)
			quoted = !quoted;
		else if (glob && quoted && *s == '*')
			res[i++] = STAR_MARK;
		else
			res[i++] = *s;
		s++;
	}
	res[i] = '\0';
	return (res);
}
