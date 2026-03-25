/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 05:52:27 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/22 14:11:37 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"

static bool	map_detected(const char *line)
{
	if (!line || !*line || *line == '\n')
		return (false);
	while (*line && ft_isset(*line, MAP_SET))
		line++;
	return (*line == '\n' || !*line);
}

static bool	check_syntax(size_t line_n)
{
	if (ft_strtok(NULL, SPACE_CHARS))
		return (parse_error(INVALID, SYNTAX, line_n), false);
	return (true);
}

static bool	check_tokens(char *line, size_t line_n, t_data *data)
{
	int8_t	id;
	bool	ret;
	char	*token;

	token = ft_strtok(line, SPACE_CHARS);
	if (!token || !*token)
		return (true);
	id = check_id(token, line_n, false);
	token = ft_strtok(NULL, SPACE_CHARS);
	if (id < TEXTURE_AMOUNT)
		ret = check_link(token, line_n, data, id);
	else
		ret = check_color(token, line_n, data, id - TEXTURE_AMOUNT);
	if (!check_syntax(line_n))
		ret = false;
	return (ret);
}

int	dump(char *file_path, t_data *data)
{
	int		fd;
	bool	ret;
	char	*line;
	size_t	line_n;

	line_n = 1;
	ret = true;
	init_data(data);
	fd = open(file_path, O_RDONLY);
	if (fd == INVALID_FD)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line && !map_detected(line))
	{
		if (!check_tokens(line, line_n++, data))
			ret = false;
		free(line);
		line = get_next_line(fd);
	}
	if (!check_id(NULL, 0, CHECK_MISSING))
		ret = false;
	if (!check_map(fd, line, line_n, data))
		return (close(fd), false);
	return (close(fd), ret);
}
