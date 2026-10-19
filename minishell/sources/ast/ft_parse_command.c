/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 01:16:17 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 04:40:15 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_cmd_args(t_tokens *tokens)
{
	int	count;

	count = 0;
	while (tokens && (tokens->type == WORD || ft_is_red(tokens->type)))
	{
		if (ft_is_red(tokens->type))
			tokens = tokens->next;
		else
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_ast	*ft_parse_command(t_tokens **tokens)
{
	t_ast		*node;
	t_tokens	*tmp;
	int			i;

	node = ft_create_ast(AST_CMD);
	if (!node)
		return (NULL);
	node->argv = malloc(sizeof(char *) * (ft_count_cmd_args(*tokens) + 1));
	if (!node->argv)
		return (free(node), NULL);
	i = 0;
	tmp = *tokens;
	while (tmp && (tmp->type == WORD || ft_is_red(tmp->type)))
	{
		if (ft_is_red(tmp->type))
			tmp = tmp->next;
		else
			node->argv[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	node->argv[i] = NULL;
	return (ft_parse_redir(tokens, node));
}
