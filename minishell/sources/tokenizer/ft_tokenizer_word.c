/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:19:25 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 03:44:49 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_read_quotes(char *s, int i, bool *error)
{
	char	quote;

	quote = s[i++];
	while (s[i] && s[i] != quote)
		i++;
	if (!s[i])
	{
		*error = true;
		return (i);
	}
	return (i + 1);
}

static int	ft_read_word(char *s, int i, bool *error)
{
	while (s[i] && !ft_isspace(s[i]) && !ft_ismeta(s[i]))
	{
		if (s[i] == '\'' || s[i] == '"')
			i = ft_read_quotes(s, i, error);
		else
			i++;
	}
	return (i);
}

bool	ft_tokenizer_word(t_tokens **tokens, char *s, int *start)
{
	int		i;
	bool	error;
	char	*word;

	error = false;
	i = ft_read_word(s, *start, &error);
	if (error)
	{
		ft_putstr_fd(2, "syntax error: unclosed quote\n");
		return (false);
	}
	word = ft_substr(s, *start, i - *start);
	ft_lst_addback((void **)tokens,
		ft_create_token(word, WORD));
	free(word);
	*start = i;
	return (true);
}
