/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:51:42 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 01:22:27 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_clean_tokens(t_tokens *tokens)
{
	t_tokens	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

static void	ft_clean_ast(t_ast *ast)
{
	int	i;

	if (!ast)
		return ;
	ft_clean_ast(ast->left);
	ft_clean_ast(ast->right);
	if (ast->argv)
	{
		i = 0;
		while (ast->argv[i])
			free(ast->argv[i++]);
		free(ast->argv);
	}
	if (ast->file)
		free(ast->file);
	free(ast);
}

void	ft_mini_clean(t_shell *shell)
{
	if (!shell)
		return ;
	ft_clean_tokens(shell->tokens);
	ft_clean_ast(shell->ast);
	if (shell->input)
		free(shell->input);
	shell->tokens = NULL;
	shell->ast = NULL;
	shell->input = NULL;
}
