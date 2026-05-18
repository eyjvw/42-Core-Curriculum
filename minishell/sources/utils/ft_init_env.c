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

static void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
}

void	ft_init_env(t_shell *shell, char **env)
{
	int		i;
	char	**split;
	t_env	*new;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (split && split[0])
		{
			new = ft_create_env(split[0], split[1]);
			if (new)
				ft_lst_addback((void **)&shell->env, new);
		}
		ft_free_split(split);
		i++;
	}
}
