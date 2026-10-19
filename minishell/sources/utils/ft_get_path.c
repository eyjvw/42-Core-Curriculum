/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 01:27:54 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/09 03:05:50 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_paths(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static char	*ft_search_path(char **paths, char *cmd, int mode)
{
	char		*tmp;
	char		*path;
	struct stat	st;
	int			i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i++], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (path && access(path, mode) == 0 && stat(path, &st) == 0
			&& !S_ISDIR(st.st_mode))
			return (path);
		free(path);
	}
	return (NULL);
}

char	*ft_get_path(t_shell *shell, char *cmd)
{
	char	**paths;
	char	*path;
	char	*tmp;

	if (!*cmd)
		return (NULL);
	tmp = ft_get_env(shell->env, "PATH");
	if (ft_strchr(cmd, '/') || !tmp)
		return (ft_strdup(cmd));
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	path = ft_search_path(paths, cmd, X_OK);
	if (!path)
		path = ft_search_path(paths, cmd, F_OK);
	ft_free_paths(paths);
	return (path);
}
