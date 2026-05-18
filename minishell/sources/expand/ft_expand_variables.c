/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:18:14 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/08 03:51:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_expand_exit_code(t_shell *shell, char *res)
{
	char	*temp;

	temp = ft_itoa(shell->exit_code);
	res = ft_strjoin_and_free(res, temp);
	free(temp);
	return (res);
}

static char	*ft_expand_pid(char *res)
{
	char	*temp;

	temp = ft_itoa((int)getpid());
	res = ft_strjoin_and_free(res, temp);
	free(temp);
	return (res);
}

static char	*ft_expand_var_name(t_shell *shell, char *value, int *i, char *res)
{
	int		start;
	int		len;
	char	*var;
	char	*temp;

	start = *i;
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	len = *i - start;
	if (len > 0)
	{
		var = ft_substr(value, start, len);
		temp = ft_get_env(shell->env, var);
		if (temp)
			res = ft_strjoin_and_free(res, temp);
		free(var);
	}
	else
		res = ft_strjoin_and_free(res, "$");
	return (res);
}

static char	*ft_handle_dollar(t_shell *shell, char *value, int *i, char *res)
{
	(*i)++;
	if (value[*i] == '?')
	{
		res = ft_expand_exit_code(shell, res);
		(*i)++;
	}
	else if (value[*i] == '$')
	{
		res = ft_expand_pid(res);
		(*i)++;
	}
	else
		res = ft_expand_var_name(shell, value, i, res);
	return (res);
}

char	*ft_expand_variables(t_shell *shell, char *value)
{
	int		i;
	char	*res;
	char	buf[2];

	i = 0;
	res = ft_strdup("");
	while (value[i])
	{
		if (value[i] == '$')
			res = ft_handle_dollar(shell, value, &i, res);
		else
		{
			buf[0] = value[i];
			buf[1] = '\0';
			res = ft_strjoin_and_free(res, buf);
			i++;
		}
	}
	return (res);
}
