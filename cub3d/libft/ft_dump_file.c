/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:50:06 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/18 04:31:05 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**update_buffer(char **file, char *line, size_t index, size_t *size)
{
	if (index == *size)
	{
		file = ft_double_realloc(file, *size, *size * 2);
		if (file == NULL)
			return (NULL);
		*size *= 2;
	}
	file[index] = ft_strdup(line);
	if (file[index] == NULL)
		return (ft_double_free(file), NULL);
	return (file);
}

static bool	init_dump(char *file_path, int *fd, char **line, char ***file)
{
	size_t	i;

	i = 0;
	if (FILE_BUFFER_SIZE == 0)
		return (false);
	*fd = open(file_path, O_RDONLY);
	if (*fd == -1)
		return (false);
	*line = get_next_line(*fd);
	if (!*line)
		return (false);
	*file = malloc(sizeof(char *) * FILE_BUFFER_SIZE);
	if (!*file)
		return (free(*line), false);
	(*file)[0] = ft_strdup(*line);
	while (++i < FILE_BUFFER_SIZE)
		(*file)[i] = NULL;
	if (!*file[0])
		return (free(*line), free(*file), false);
	return (true);
}

char	**ft_dump_file(char *file_path)
{
	size_t	i;
	int		fd;
	size_t	size;
	char	*line;
	char	**file;

	i = 1;
	size = FILE_BUFFER_SIZE;
	if (!init_dump(file_path, &fd, &line, &file))
		return (NULL);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		file = update_buffer(file, line, i, &size);
		if (!file)
			return (file);
		i++;
	}
	file = ft_double_realloc(file, size, i + 1);
	file[i] = NULL;
	return (file);
}
