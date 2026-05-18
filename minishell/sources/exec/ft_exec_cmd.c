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

static void	ft_child_exec(t_shell *shell, t_ast *node)
{
	char	*path;
	char	**env;

	path = ft_get_path(shell, node->argv[0]);
	if (!path)
	{
		ft_putstr_fd(2, node->argv[0]);
		ft_putstr_fd(2, COMMAND_NOT_FOUND);
		ft_final_clean(shell);
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	env = ft_env_to_arr(shell->env);
	execve(path, node->argv, env);
	perror(node->argv[0]);
	free(path);
	ft_final_clean(shell);
	exit(EXIT_FOUND_BUT_NOT_EXECUTABLE);
}

int	ft_exec_cmd(t_shell *shell, t_ast *node)
{
	pid_t	pid;
	int		status;

	if (!node->argv || !node->argv[0])
		return (0);
	if (ft_is_builtin(node->argv[0]))
		return (ft_exec_builtin(shell, node->argv));
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		ft_reset();
		ft_child_exec(shell, node);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (EXIT_COMMAND_FAILED + WTERMSIG(status));
	return (1);
}
