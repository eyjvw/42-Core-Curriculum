/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 04:24:15 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 03:09:40 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(STDOUT_FILENO, env->key);
			ft_putstr_fd(STDOUT_FILENO, "=");
			ft_putstr_fd(STDOUT_FILENO, env->value);
			ft_putstr_fd(STDOUT_FILENO, "\n");
		}
		env = env->next;
	}
	return (0);
}
