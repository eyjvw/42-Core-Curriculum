/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:17:22 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 01:00:22 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tokenizer(t_shell *shell)
{
	int			i;

	shell->tokens = NULL;
	i = 0;
	while (shell->input[i])
	{
		while (ft_isspace(shell->input[i]))
			i++;
		if (!shell->input[i])
			break ;
		if (ft_ismeta(shell->input[i]))
			ft_tokenizer_meta(&shell->tokens, shell->input, &i);
		else
		{
			if (!ft_tokenizer_word(&shell->tokens, shell->input, &i))
			{
				shell->tokens = NULL;
				return ;
			}
		}
	}
}
