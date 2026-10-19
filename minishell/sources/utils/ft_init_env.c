/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:14:54 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/07 03:37:41 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_env(t_shell *shell, char **env)
{
	int		i;
	char	*eq;
	char	*key;
	t_env	*new;

	i = 0;
	while (env[i])
	{
		eq = ft_strchr(env[i], '=');
		if (eq)
		{
			key = ft_substr(env[i], 0, eq - env[i]);
			new = ft_create_env(key, eq + 1);
			if (new)
				ft_lst_addback((void **)&shell->env, new);
			free(key);
		}
		i++;
	}
}
