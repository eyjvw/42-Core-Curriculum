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
	while (tokens && tokens->type == WORD && !ft_is_red(tokens->type))
	{
		count++;
		tokens = tokens->next;
		if (tokens && ft_is_red(tokens->type))
			break ;
	}
	return (count);
}

static bool	ft_is_end_of_cmd(t_tokens *tokens)
{
	if (!tokens)
		return (true);
	if (tokens->type != WORD)
		return (true);
	return (false);
}

t_ast	*ft_parse_command(t_tokens **tokens)
{
	t_ast	*node;
	int		argc;
	int		i;

	if (!*tokens || (*tokens)->type != WORD)
		return (NULL);
	node = ft_create_ast(AST_CMD);
	if (!node)
		return (NULL);
	argc = ft_count_cmd_args(*tokens);
	node->argv = malloc(sizeof(char *) * (argc + 1));
	if (!node->argv)
		return (free(node), NULL);
	i = 0;
	while (!ft_is_end_of_cmd(*tokens))
	{
		node->argv[i++] = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	node->argv[i] = NULL;
	return (node);
}
