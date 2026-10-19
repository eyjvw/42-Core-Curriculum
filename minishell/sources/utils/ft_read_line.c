/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/10/19 12:00:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_read_line(int fd)
{
	char	*line;
	char	buf[2];
	ssize_t	ret;

	line = NULL;
	buf[1] = '\0';
	ret = read(fd, buf, 1);
	while (ret > 0 && buf[0] != '\n')
	{
		line = ft_strjoin_and_free(line, buf);
		if (!line)
			return (NULL);
		ret = read(fd, buf, 1);
	}
	if (!line && ret > 0)
		line = ft_strdup("");
	return (line);
}

char	*ft_read_all(int fd)
{
	char	*res;
	char	buf[READ_BUFFER + 1];
	ssize_t	ret;

	res = ft_strdup("");
	ret = 1;
	while (res && ret > 0)
	{
		ret = read(fd, buf, READ_BUFFER);
		if (ret > 0)
		{
			buf[ret] = '\0';
			res = ft_strjoin_and_free(res, buf);
		}
	}
	return (res);
}

char	*ft_get_line(t_shell *shell, char *prompt)
{
	if (shell->interactive)
		return (readline(prompt));
	return (ft_read_line(STDIN_FILENO));
}
