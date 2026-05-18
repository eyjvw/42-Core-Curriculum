/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:53:47 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 04:01:04 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

static void	ft_set_env_var(t_shell *shell, char *key, char *value)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->key && !ft_strcmp(env->key, key))
		{
			if (env->value)
				free(env->value);
			if (value)
				env->value = ft_strdup(value);
			else
				env->value = NULL;
			return ;
		}
		env = env->next;
	}
	ft_add_env(shell, key, value);
}

int	ft_export(t_shell *shell, char **argv)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
		{
			key = ft_substr(argv[i], 0, eq - argv[i]);
			value = ft_strdup(eq + 1);
			ft_set_env_var(shell, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}
