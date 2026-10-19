/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_final_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student,42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:48:11 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/14 04:28:42 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_final_clean(t_shell *shell)
{
	t_env	*temp;

	if (!shell)
		return ;
	ft_mini_clean(shell);
	while (shell->env)
	{
		temp = shell->env;
		shell->env = shell->env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	shell->env = NULL;
	rl_clear_history();
}

void	ft_exit_child(t_shell *shell, int code)
{
	ft_final_clean(shell);
	exit(code);
}
