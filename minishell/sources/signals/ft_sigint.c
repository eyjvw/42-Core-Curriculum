/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:09:42 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 02:20:49 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_sigint_exec(int sig)
{
	g_signal = sig;
}

static void	ft_sigint_prompt(int sig)
{
	g_signal = sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigint(t_state_type type)
{
	if (type == PROMPT)
		signal(SIGINT, ft_sigint_prompt);
	else if (type == EXEC)
		signal(SIGINT, ft_sigint_exec);
	else if (type == STATE_HERE_DOC)
		signal(SIGINT, SIG_DFL);
}
