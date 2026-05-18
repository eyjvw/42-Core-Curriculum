/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:03:24 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 03:41:16 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_list(t_tokens *list)
{
	t_tokens	*tmp;

	while (list)
	{
		tmp = list->next;
		if (list->value)
			free(list->value);
		free(list);
		list = tmp;
	}
}

static void	ft_add_wildcard(t_tokens **new, t_tokens *wild, char *expanded)
{
	t_tokens	*tmp;

	tmp = wild;
	while (tmp)
	{
		ft_lst_addback((void **)new,
			ft_create_token(ft_strdup(tmp->value), WORD));
		tmp = tmp->next;
	}
	ft_free_list(wild);
	free(expanded);
}

static void	ft_expand_word(t_shell *shell, t_tokens *token, t_tokens **new)
{
	char		*expanded;
	char		*no_quotes;
	t_tokens	*wild;

	expanded = ft_expand_variables(shell, token->value);
	no_quotes = ft_remove_quotes(expanded);
	free(expanded);
	if (ft_strchr(no_quotes, '*'))
	{
		wild = ft_expand_wildcards(no_quotes);
		if (wild)
		{
			ft_add_wildcard(new, wild, no_quotes);
			return ;
		}
		free(no_quotes);
		return ;
	}
	ft_lst_addback((void **)new, ft_create_token(no_quotes, WORD));
	free(no_quotes);
}

void	ft_expand(t_shell *shell)
{
	t_tokens	*tokens;
	t_tokens	*new;

	tokens = shell->tokens;
	new = NULL;
	while (tokens)
	{
		if (tokens->type == WORD)
			ft_expand_word(shell, tokens, &new);
		else
			ft_lst_addback((void **)&new,
				ft_create_token(ft_strdup(tokens->value), tokens->type));
		tokens = tokens->next;
	}
	ft_mini_clean(shell);
	shell->tokens = new;
}
