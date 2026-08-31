/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 04:16:36 by sbonneau          #+#    #+#             */
/*   Updated: 2026/08/31 12:00:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Reads BUFFER_SIZE bytes at a time into the stash, and stops as soon as a
** newline is available or the file descriptor is exhausted. Nothing is read
** when the stash already holds a complete line.
*/
static char	*ft_fill(char *stash, int fd)
{
	char	*chunk;
	char	*joined;
	ssize_t	bytes;

	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (free(stash), NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, chunk, BUFFER_SIZE);
		if (bytes < 0)
			return (free(chunk), free(stash), NULL);
		chunk[bytes] = '\0';
		joined = ft_strjoin(stash, chunk);
		free(stash);
		stash = joined;
		if (!stash)
			return (free(chunk), NULL);
	}
	return (free(chunk), stash);
}

/*
** Cuts the leading line (newline included, when present) out of the stash and
** replaces the stash with whatever follows it.
*/
static char	*ft_extract(char **stash)
{
	char	*line;
	char	*rest;
	size_t	len;

	if (!*stash || !**stash)
		return (NULL);
	len = 0;
	while ((*stash)[len] && (*stash)[len] != '\n')
		len++;
	if ((*stash)[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strncpy(line, *stash, len);
	line[len] = '\0';
	if (!(*stash)[len])
		return (free(*stash), *stash = NULL, line);
	rest = malloc(ft_strlen(*stash + len) + 1);
	if (!rest)
		return (free(line), NULL);
	ft_strcpy(rest, *stash + len);
	return (free(*stash), *stash = rest, line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), stash = NULL, NULL);
	stash = ft_fill(stash, fd);
	if (!stash)
		return (NULL);
	line = ft_extract(&stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	return (line);
}
