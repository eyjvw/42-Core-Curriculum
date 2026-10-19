/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:32:18 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 04:01:16 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_atol(char *s, long *n)
{
	unsigned long	res;
	unsigned long	limit;
	int				i;

	i = 0;
	res = 0;
	while (ft_isspace(s[i]))
		i++;
	limit = (unsigned long)LONG_MAX + (s[i] == '-');
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (s[i] < '0' || s[i] > '9')
		return (false);
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (res > (limit - (s[i] - '0')) / 10)
			return (false);
		res = res * 10 + (s[i++] - '0');
	}
	while (ft_isspace(s[i]))
		i++;
	if (limit > (unsigned long)LONG_MAX)
		res = -res;
	*n = (long)res;
	return (s[i] == '\0');
}

int	ft_exit(t_shell *shell, char **argv)
{
	long	n;
	int		code;

	if (shell->interactive)
		ft_putstr_fd(STDERR_FILENO, "exit\n");
	code = shell->exit_code;
	if (argv[1] && !ft_atol(argv[1], &n))
	{
		ft_error("exit", argv[1], "numeric argument required");
		code = 2;
	}
	else if (argv[1] && argv[2])
		return (ft_error("exit", NULL, "too many arguments"), 1);
	else if (argv[1])
		code = (unsigned char)n;
	ft_exit_child(shell, code);
	return (0);
}
