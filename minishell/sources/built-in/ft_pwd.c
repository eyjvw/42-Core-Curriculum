/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 04:22:48 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 02:39:38 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_shell *shell)
{
	t_env	*env;
	char	*cwd;

	env = shell->env;
	cwd = NULL;
	while (env)
	{
		if (env->key && !ft_strcmp(env->key, "PWD"))
		{
			printf("%s\n", env->value);
			return (EXIT_SUCCESS);
		}
		env = env->next;
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (EXIT_SUCCESS);
	}
	else
		return (perror("pwd"), EXIT_FAILURE);
}
