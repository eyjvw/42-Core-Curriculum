/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:40:51 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 02:35:19 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_exec_fail(t_shell *shell, char *cmd, char *path)
{
	int	code;

	code = EXIT_FOUND_BUT_NOT_EXECUTABLE;
	if (errno == ENOENT)
		code = EXIT_COMMAND_NOT_FOUND;
	ft_error(cmd, NULL, strerror(errno));
	free(path);
	ft_exit_child(shell, code);
}

static void	ft_child_exec(t_shell *shell, t_ast *node)
{
	char		*path;
	char		**env;
	struct stat	st;

	ft_close_fds(shell->ast);
	path = ft_get_path(shell, node->argv[0]);
	if (!path)
	{
		ft_error(node->argv[0], NULL, COMMAND_NOT_FOUND);
		ft_exit_child(shell, EXIT_COMMAND_NOT_FOUND);
	}
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		errno = EISDIR;
	else
	{
		env = ft_env_to_arr(shell->env);
		execve(path, node->argv, env);
		ft_free_arr(env);
	}
	ft_exec_fail(shell, node->argv[0], path);
}

int	ft_exec_cmd(t_shell *shell, t_ast *node)
{
	pid_t	pid;
	char	**argv;

	argv = ft_expand_argv(shell, node->argv);
	if (!argv)
		return (1);
	ft_free_arr(node->argv);
	node->argv = argv;
	if (!argv[0])
		return (0);
	if (ft_is_builtin(argv[0]))
		return (ft_exec_builtin(shell, argv));
	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), 1);
	if (pid == 0)
	{
		ft_reset();
		ft_child_exec(shell, node);
	}
	return (ft_wait(shell, pid));
}
