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

static int	ft_cd_home(t_shell *shell, char **target, char *oldpwd)
{
	*target = ft_get_env(shell->env, "HOME");
	if (!*target)
	{
		ft_putstr_fd(2, "cd: HOME not set\n");
		free(oldpwd);
		return (1);
	}
	return (0);
}

static int	ft_cd_oldpwd(t_shell *shell, char **target, char *oldpwd)
{
	*target = ft_get_env(shell->env, "OLDPWD");
	if (!*target)
	{
		ft_putstr_fd(2, "cd: OLDPWD not set\n");
		free(oldpwd);
		return (1);
	}
	printf("%s\n", *target);
	return (0);
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
	int		ret;

	oldpwd = getcwd(NULL, 0);
	target = NULL;
	if (!argv[1] || !argv[1][0])
	{
		if (ft_cd_home(shell, &target, oldpwd))
			return (1);
	}
	else if (argv[1][0] == '-' && !argv[1][1])
	{
		if (ft_cd_oldpwd(shell, &target, oldpwd))
			return (1);
	}
	else
		target = argv[1];
	ret = chdir(target);
	if (ret != 0)
		return (perror("cd"), free(oldpwd), 1);
	ft_update_pwd(shell, oldpwd);
	free(oldpwd);
	return (0);
}
