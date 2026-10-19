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

static char	*ft_append(char *res, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (ft_strjoin_and_free(res, buf));
}

static bool	ft_is_quote(char *state, char c)
{
	if (c != '\'' && c != '"')
		return (false);
	if (!*state)
		*state = c;
	else if (*state == c)
		*state = 0;
	else
		return (false);
	return (true);
}

static char	*ft_expand_var_name(t_shell *shell, char *value, int *i, char *res)
{
	int		start;
	char	*var;

	start = *i;
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	var = ft_substr(value, start, *i - start);
	if (var)
		res = ft_strjoin_and_free(res, ft_get_env(shell->env, var));
	free(var);
	return (res);
}

static char	*ft_handle_dollar(t_shell *shell, char *value, int *i, char *res)
{
	char	*temp;

	temp = NULL;
	(*i)++;
	if (value[*i] == '?')
		temp = ft_itoa(shell->exit_code);
	else if (value[*i] == '0')
		temp = ft_strdup("minishell");
	if (value[*i] == '?' || (value[*i] >= '0' && value[*i] <= '9'))
	{
		res = ft_strjoin_and_free(res, temp);
		free(temp);
		(*i)++;
	}
	else if (ft_isalnum(value[*i]) || value[*i] == '_')
		res = ft_expand_var_name(shell, value, i, res);
	else
		res = ft_append(res, '$');
	return (res);
}

char	*ft_expand_variables(t_shell *shell, char *value, bool quotes)
{
	int		i;
	char	*res;
	char	state;

	i = 0;
	state = 0;
	res = ft_strdup("");
	while (res && value[i])
	{
		if (value[i] == '$' && quotes && !state
			&& (value[i + 1] == '\'' || value[i + 1] == '"'))
			i++;
		else if (value[i] == '$' && state != '\'')
			res = ft_handle_dollar(shell, value, &i, res);
		else
		{
			if (quotes && ft_is_quote(&state, value[i]))
				res = ft_append(res, QUOTE_MARK);
			else
				res = ft_append(res, value[i]);
			i++;
		}
	}
	return (res);
}
