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

static void	ft_minishell(t_shell *shell)
{
	while (1)
	{
		ft_sigint(PROMPT);
		if (isatty(STDIN_FILENO))
			shell->input = readline(BLUE "golem" WHITE "shell" RED "> " RESET);
		else
			shell->input = readline(NULL);
		if (!shell->input)
			break ;
		if (*shell->input)
		{
			add_history(shell->input);
			ft_tokenizer(shell);
			if (ft_check_args(shell->tokens))
			{
				ft_expand(shell);
				ft_ast(shell);
				ft_exec_ast(shell);
			}
		}
		ft_mini_clean(shell);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	(void)env;
	ft_bzero(&shell, sizeof(t_shell));
	ft_init_env(&shell, env);
	ft_sigquit();
	ft_minishell(&shell);
	ft_final_clean(&shell);
	return (0);
}
