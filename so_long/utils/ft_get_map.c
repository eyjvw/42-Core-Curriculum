/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 03:54:05 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/11 04:00:54 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_check_empty(char *map)
{
	size_t	i;

	i = 0;
	if (map[0] == '\n')
		return (0);
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_ext(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5 || filename[len - 5] == '/')
		return (0);
	return (filename[len - 4] == '.' && filename[len - 3] == 'b'
		&& filename[len - 2] == 'e' && filename[len - 1] == 'r');
}

char	**ft_get_map(const char *filename)
{
	int		fd;
	char	*buffer;
	char	**map;

	if (!ft_check_ext(filename))
		return (ft_perror(ERR_EXTENSION), NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_perror(ERR_INVALID_FILE), NULL);
	buffer = ft_read(fd);
	close(fd);
	if (!buffer)
		return (ft_perror(ERR_READ_MAP), NULL);
	if (ft_strlen(buffer) > MAX_FILE_SIZE)
		return (free(buffer), ft_perror(ERR_FILE_TOO_BIG), NULL);
	if (!buffer[0])
		return (free(buffer), ft_perror(ERR_NO_DATA), NULL);
	if (!ft_check_empty(buffer))
		return (free(buffer), ft_perror(ERR_EMPTY_LINE), NULL);
	map = ft_split(buffer, '\n');
	free(buffer);
	if (!map)
		ft_perror(ERR_MEMORY_MAP);
	return (map);
}
