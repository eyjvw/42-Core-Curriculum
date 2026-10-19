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

static void	ft_print_var(t_env *var)
{
	int	i;

	ft_putstr_fd(STDOUT_FILENO, "declare -x ");
	ft_putstr_fd(STDOUT_FILENO, var->key);
	if (var->value)
	{
		ft_putstr_fd(STDOUT_FILENO, "=\"");
		i = 0;
		while (var->value[i])
		{
			if (ft_strchr("\"\\$`", var->value[i]))
				write(STDOUT_FILENO, "\\", 1);
			write(STDOUT_FILENO, &var->value[i++], 1);
		}
		ft_putstr_fd(STDOUT_FILENO, "\"");
	}
	ft_putstr_fd(STDOUT_FILENO, "\n");
}

static void	ft_print_export(t_env *env)
{
	t_env	*last;
	t_env	*min;
	t_env	*curr;

	last = NULL;
	while (1)
	{
		min = NULL;
		curr = env;
		while (curr)
		{
			if ((!last || ft_strcmp(curr->key, last->key) > 0)
				&& (!min || ft_strcmp(curr->key, min->key) < 0))
				min = curr;
			curr = curr->next;
		}
		if (!min)
			return ;
		if (ft_strcmp(min->key, "_"))
			ft_print_var(min);
		last = min;
	}
}

static int	ft_export_arg(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;
	char	*value;
	int		len;

	eq = ft_strchr(arg, '=');
	len = ft_strlen(arg);
	if (eq)
		len = eq - arg;
	if (eq && len > 0 && arg[len - 1] == '+')
		len--;
	if (!ft_valid_id(arg, len))
		return (ft_invalid_id("export", arg), 1);
	key = ft_substr(arg, 0, len);
	value = NULL;
	if (key && eq && arg[len] == '+')
		value = ft_strjoin(ft_get_env(shell->env, key), eq + 1);
	else if (eq)
		value = ft_strdup(eq + 1);
	if (key && (eq || !ft_get_env(shell->env, key)))
		ft_add_env(shell, key, value);
	free(key);
	free(value);
	return (0);
}

int	ft_export(t_shell *shell, char **argv)
{
	int	i;
	int	ret;

	if (!argv[1])
		return (ft_print_export(shell->env), 0);
	i = 1;
	ret = 0;
	while (argv[i])
	{
		if (ft_export_arg(shell, argv[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
