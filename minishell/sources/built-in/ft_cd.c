/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:15:23 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 03:30:43 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>

static char	*ft_cd_target(t_shell *shell, char **argv)
{
	char	*target;

	if (!argv[1])
	{
		target = ft_get_env(shell->env, "HOME");
		if (!target)
			ft_error("cd", NULL, "HOME not set");
		return (target);
	}
	if (!ft_strcmp(argv[1], "-"))
	{
		target = ft_get_env(shell->env, "OLDPWD");
		if (!target)
			ft_error("cd", NULL, "OLDPWD not set");
		return (target);
	}
	return (argv[1]);
}

static void	ft_update_pwd(t_shell *shell, char *oldpwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_add_env(shell, "OLDPWD", oldpwd);
		ft_add_env(shell, "PWD", cwd);
		free(cwd);
	}
}

int	ft_cd(t_shell *shell, char **argv)
{
	char	*target;
	char	*oldpwd;

	if (argv[1] && argv[2])
		return (ft_error("cd", NULL, "too many arguments"), 1);
	target = ft_cd_target(shell, argv);
	if (!target)
		return (1);
	if (!*target)
		return (0);
	oldpwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		ft_error("cd", target, strerror(errno));
		return (free(oldpwd), 1);
	}
	if (argv[1] && !ft_strcmp(argv[1], "-"))
	{
		ft_putstr_fd(STDOUT_FILENO, target);
		ft_putstr_fd(STDOUT_FILENO, "\n");
	}
	ft_update_pwd(shell, oldpwd);
	free(oldpwd);
	return (0);
}
