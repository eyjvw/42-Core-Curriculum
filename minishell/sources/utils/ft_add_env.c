/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:22:38 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 04:01:59 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <string.h>

static int	ft_update_env(t_env *start, t_env *stop, char *key, char *value)
{
	while (start && start != stop)
	{
		if (start->key && !ft_strcmp(start->key, key))
		{
			free(start->value);
			start->value = ft_strdup(value);
			return (1);
		}
		start = start->next;
	}
	return (0);
}

static void	ft_insert_env(t_shell *shell, char *key, char *value)
{
	t_env	*prev;
	t_env	*curr;
	t_env	*new;

	prev = NULL;
	curr = shell->env;
	while (curr && curr->next && curr->next->key
		&& ft_strcmp(curr->next->key, "_"))
	{
		prev = curr;
		curr = curr->next;
	}
	new = ft_create_env(key, value);
	if (!new)
		return ;
	if (!prev)
	{
		new->next = shell->env;
		shell->env = new;
	}
	else
	{
		new->next = curr->next;
		curr->next = new;
	}
}

void	ft_add_env(t_shell *shell, char *key, char *value)
{
	t_env	*curr;

	curr = shell->env;
	while (curr && curr->next && curr->next->key
		&& ft_strcmp(curr->next->key, "_"))
		curr = curr->next;
	if (ft_update_env(shell->env, curr->next, key, value))
		return ;
	ft_insert_env(shell, key, value);
}
