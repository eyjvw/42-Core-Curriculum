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

static void	ft_syntax_error(char *token)
{
	ft_putstr_fd(2, UNEXCEPTED_TOKEN);
	ft_putstr_fd(2, token);
	ft_putstr_fd(2, "'\n");
}

static bool	ft_check_parentheses(t_tokens *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == LPAREN)
			count++;
		else if (tokens->type == RPAREN)
		{
			count--;
			if (count < 0)
				return (ft_syntax_error(")"), false);
		}
		tokens = tokens->next;
	}
	if (count > 0)
		return (ft_syntax_error("("), false);
	return (true);
}

static bool	ft_check_operators(t_tokens *tokens)
{
	if (ft_is_op(tokens->type))
		return (ft_syntax_error(tokens->value), false);
	while (tokens)
	{
		if (ft_is_op(tokens->type))
		{
			if (!tokens->next)
				return (ft_syntax_error(tokens->value), false);
			if (ft_is_op(tokens->next->type))
				return (ft_syntax_error(tokens->next->value), false);
		}
		if (ft_is_red(tokens->type))
		{
			if (!tokens->next)
				return (ft_syntax_error("newline"), false);
			if (tokens->next->type != WORD)
				return (ft_syntax_error(tokens->next->value), false);
		}
		tokens = tokens->next;
	}
	return (true);
}

bool	ft_check_args(t_tokens *tokens)
{
	if (!tokens)
		return (false);
	if (!ft_check_parentheses(tokens))
		return (false);
	if (!ft_check_operators(tokens))
		return (false);
	return (true);
}
