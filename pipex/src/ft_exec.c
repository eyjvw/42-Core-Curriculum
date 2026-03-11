/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:34:39 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 05:39:42 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_direct_path(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	return (NULL);
}

static char	*ft_search_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*temp;
	char	*full;

	if (!cmd || !env)
		return (NULL);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full, X_OK) == 0)
			return (ft_free_split(paths, -1), full);
		(free(full), i++);
	}
	return (ft_free_split(paths, -1), NULL);
}

static char	*ft_get_path(char *cmd, char **env)
{
	char	*p;

	p = ft_direct_path(cmd);
	if (p)
		return (p);
	return (ft_search_path(cmd, env));
}

void	ft_exec(t_pipex *px, char *cmd)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = ft_get_path(args[0], px->env);
	if (!path)
	{
		ft_free_split(args, -1);
		ft_close(px);
		ft_putstr_fd(2, args[0]);
		ft_putstr_fd(2, ": command not found\n");
		exit(127);
	}
	execve(path, args, px->env);
	ft_putstr_fd(2, "execve failed\n");
	if (path != args[0])
		free(path);
	ft_free_split(args, -1);
	exit(1);
}
