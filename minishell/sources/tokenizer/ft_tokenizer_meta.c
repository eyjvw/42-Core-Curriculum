/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_meta.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:14:24 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/08 04:00:13 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_create_and_add(t_tokens **tokens, char *value, t_token_type type)
{
	ft_lst_addback((void **)tokens,
		ft_create_token(ft_strdup(value), type));
}

static bool	ft_tokenizer_meta_bonus(t_tokens **tokens, char *s, int *i)
{
	if (s[*i] == '&' && s[*i + 1] == '&')
		return (ft_create_and_add(tokens, "&&", AND_IF), *i += 2, true);
	else if (s[*i] == '|' && s[*i + 1] == '|')
		return (ft_create_and_add(tokens, "||", OR_IF), *i += 2, true);
	else if (s[*i] == '(')
		return (ft_create_and_add(tokens, "(", LPAREN), (*i)++, true);
	else if (s[*i] == ')')
		return (ft_create_and_add(tokens, ")", RPAREN), (*i)++, true);
	return (false);
}

static bool	ft_tokenizer_meta_mandatory(t_tokens **tokens, char *s, int *i)
{
	if (s[*i] == '>' && s[*i + 1] == '>')
		return (ft_create_and_add(tokens, ">>", APPEND), *i += 2, true);
	else if (s[*i] == '<' && s[*i + 1] == '<')
		return (ft_create_and_add(tokens, "<<", HERE_DOC), *i += 2, true);
	else if (s[*i] == '>')
		return (ft_create_and_add(tokens, ">", REDIR_OUT), (*i)++, true);
	else if (s[*i] == '<')
		return (ft_create_and_add(tokens, "<", REDIR_IN), (*i)++, true);
	else if (s[*i] == '|')
		return (ft_create_and_add(tokens, "|", PIPE), (*i)++, true);
	return (false);
}

void	ft_tokenizer_meta(t_tokens **tokens, char *s, int *i)
{
	if (ft_tokenizer_meta_bonus(tokens, s, i))
		return ;
	ft_tokenizer_meta_mandatory(tokens, s, i);
}
