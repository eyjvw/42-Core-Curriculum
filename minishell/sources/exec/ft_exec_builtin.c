/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:57:41 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 03:55:04 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_builtin(t_shell *shell, char **argv)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv));
	if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(shell, argv));
	if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd(shell));
	if (!ft_strcmp(argv[0], "export"))
		return (ft_export(shell, argv));
	if (!ft_strcmp(argv[0], "unset"))
		return (ft_unset(shell, argv));
	if (!ft_strcmp(argv[0], "env"))
		return (ft_env(shell));
	if (!ft_strcmp(argv[0], "exit"))
		return (ft_exit(shell));
	return (0);
}
