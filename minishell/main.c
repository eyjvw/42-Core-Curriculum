/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:29:23 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 03:59:27 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

volatile sig_atomic_t	g_signal;

static void	ft_run_line(t_shell *shell)
{
	int	ret;

	if (!ft_tokenizer(shell))
	{
		shell->exit_code = 2;
		return ;
	}
	if (!shell->tokens)
		return ;
	if (!ft_check_args(shell->tokens))
	{
		shell->exit_code = 2;
		return ;
	}
	ft_ast(shell);
	ft_sigint(EXEC);
	ret = ft_heredocs(shell, shell->ast);
	if (ret)
	{
		shell->exit_code = ret;
		return ;
	}
	ft_exec_ast(shell);
}

static void	ft_minishell(t_shell *shell)
{
	while (1)
	{
		ft_sigint(PROMPT);
		g_signal = 0;
		shell->input = ft_get_line(shell,
				BLUE "golem" WHITE "shell" RED "> " RESET);
		if (g_signal == SIGINT)
			shell->exit_code = SIGNAL_INTERUP;
		if (!shell->input)
			break ;
		if (*shell->input && shell->interactive)
			add_history(shell->input);
		ft_run_line(shell);
		ft_mini_clean(shell);
	}
	if (shell->interactive)
		ft_putstr_fd(STDERR_FILENO, "exit\n");
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	int		code;

	(void)ac;
	(void)av;
	ft_bzero(&shell, sizeof(t_shell));
	shell.interactive = isatty(STDIN_FILENO);
	ft_init_env(&shell, env);
	ft_sigquit();
	ft_minishell(&shell);
	code = shell.exit_code;
	ft_final_clean(&shell);
	return (code);
}
