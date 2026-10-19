/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *cmd, char *arg, char *msg)
{
	char	*s;

	s = ft_strdup("minishell: ");
	if (cmd)
		s = ft_strjoin_and_free(ft_strjoin_and_free(s, cmd), ": ");
	if (arg)
		s = ft_strjoin_and_free(ft_strjoin_and_free(s, arg), ": ");
	s = ft_strjoin_and_free(ft_strjoin_and_free(s, msg), "\n");
	if (s)
		write(STDERR_FILENO, s, ft_strlen(s));
	free(s);
}

void	ft_invalid_id(char *cmd, char *arg)
{
	char	*s;

	s = ft_strjoin("`", arg);
	s = ft_strjoin_and_free(s, "'");
	ft_error(cmd, s, "not a valid identifier");
	free(s);
}
