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
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	**ft_get_map(const char *filename)
{
	int		fd;
	char	*buffer;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		(ft_perror(ERR_INVALID_FILE), exit(1));
	buffer = ft_read(fd);
	close(fd);
	if (!buffer)
		(ft_perror(ERR_NO_DATA), exit(1));
	if (!ft_check_empty(buffer))
		return (free(buffer), NULL);
	map = ft_split(buffer, '\n');
	free(buffer);
	return (map);
}
