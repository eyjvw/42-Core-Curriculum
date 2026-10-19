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

static void	ft_exec_direct(t_pipex *px, char **args)
{
	int	code;

	execve(args[0], args, px->env);
	perror(args[0]);
	code = 126;
	if (access(args[0], F_OK) == -1)
		code = 127;
	ft_free_split(args, -1);
	exit(code);
}

static char	**ft_get_paths(char **env)
{
	int	i;

	i = 0;
	while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env || !env[i])
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

static char	*ft_search_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*temp;
	char	*full;

	if (!cmd || !*cmd)
		return (NULL);
	paths = ft_get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(temp, cmd);
		free(temp);
		if (full && access(full, X_OK) == 0)
			return (ft_free_split(paths, -1), full);
		(free(full), i++);
	}
	return (ft_free_split(paths, -1), NULL);
}

static void	ft_not_found(char **args, char *cmd)
{
	char	*msg;

	if (args[0])
		cmd = args[0];
	msg = ft_strjoin(cmd, ": command not found\n");
	if (msg)
		ft_putstr_fd(2, msg);
	free(msg);
	ft_free_split(args, -1);
	exit(127);
}

void	ft_exec(t_pipex *px, char *cmd)
{
	char	**args;
	char	*path;

	args = ft_split_cmd(cmd);
	if (!args)
		exit(1);
	if (args[0] && ft_strchr(args[0], '/'))
		ft_exec_direct(px, args);
	path = ft_search_path(args[0], px->env);
	if (!path)
		ft_not_found(args, cmd);
	execve(path, args, px->env);
	perror(args[0]);
	free(path);
	ft_free_split(args, -1);
	exit(126);
}
