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
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && ft_get_env(shell->env, "PWD"))
		cwd = ft_strdup(ft_get_env(shell->env, "PWD"));
	if (!cwd)
		return (perror("minishell: pwd"), EXIT_FAILURE);
	ft_putstr_fd(STDOUT_FILENO, cwd);
	ft_putstr_fd(STDOUT_FILENO, "\n");
	free(cwd);
	return (EXIT_SUCCESS);
}
