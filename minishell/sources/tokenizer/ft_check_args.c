/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:45:54 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 18:18:12 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_syntax_error(char *token)
{
	ft_putstr_fd(2, "minishell: " UNEXCEPTED_TOKEN);
	ft_putstr_fd(2, token);
	ft_putstr_fd(2, "'\n");
	return (false);
}

static bool	ft_eof_error(void)
{
	ft_putstr_fd(2, "minishell: syntax error: unexpected end of file\n");
	return (false);
}

static bool	ft_valid_next(t_tokens *prev, t_tokens *curr, bool subshell)
{
	if (prev && ft_is_red(prev->type))
		return (curr->type == WORD);
	if (subshell && curr->type == WORD)
		return (false);
	if (!prev || ft_is_op(prev->type) || prev->type == LPAREN)
		return (curr->type == WORD || ft_is_red(curr->type)
			|| curr->type == LPAREN);
	if (prev->type == RPAREN)
		return (ft_is_op(curr->type) || ft_is_red(curr->type)
			|| curr->type == RPAREN);
	return (curr->type != LPAREN);
}

bool	ft_check_args(t_tokens *tokens)
{
	t_tokens	*prev;
	int			depth;
	bool		subshell;

	prev = NULL;
	depth = 0;
	subshell = false;
	while (tokens)
	{
		if (!ft_valid_next(prev, tokens, subshell))
			return (ft_syntax_error(tokens->value));
		if (tokens->type == LPAREN)
			depth++;
		else if (tokens->type == RPAREN && --depth < 0)
			return (ft_syntax_error(tokens->value));
		subshell = (tokens->type == RPAREN
				|| (subshell && !ft_is_op(tokens->type)));
		prev = tokens;
		tokens = tokens->next;
	}
	if (prev && ft_is_red(prev->type))
		return (ft_syntax_error("newline"));
	if (prev && (ft_is_op(prev->type) || depth > 0))
		return (ft_eof_error());
	return (true);
}
