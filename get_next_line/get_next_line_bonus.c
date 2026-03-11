/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 07:48:12 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 05:27:42 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_copy(char *s1, char *s2)
{
	char	*s3;

	if (!s1)
		return (ft_strjoin("", s2));
	s3 = ft_strjoin(s1, s2);
	free(s1);
	if (!s3)
		return (NULL);
	return (s3);
}

static char	*ft_read(char *buffer, int fd)
{
	char		*temp;
	ssize_t		bytes;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (free(buffer), NULL);
	bytes = read(fd, temp, BUFFER_SIZE);
	if (bytes < 0)
		return (free(temp), free(buffer), NULL);
	while (bytes > 0)
	{
		temp[bytes] = '\0';
		buffer = ft_copy(buffer, temp);
		if (!buffer)
			return (free(temp), NULL);
		if (ft_strchr(temp, '\n'))
			break ;
		bytes = read(fd, temp, BUFFER_SIZE);
	}
	return (free(temp), buffer);
}

static char	*ft_line(char **str)
{
	char	*line;
	char	*newline_pos;
	size_t	len;
	char	*temp;

	if (!*str || !**str)
		return (NULL);
	newline_pos = ft_strchr(*str, '\n');
	if (newline_pos)
		len = newline_pos - *str + 1;
	else
		len = ft_strlen(*str);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strncpy(line, *str, len);
	line[len] = '\0';
	if (!newline_pos)
		return (free(*str), *str = NULL, line);
	temp = malloc(ft_strlen(newline_pos + 1) + 1);
	if (!temp)
		return (free(line), NULL);
	ft_strcpy(temp, newline_pos + 1);
	return (free(*str), *str = temp, line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
	{
		if (buffer[fd])
			free(buffer[fd]);
		return (NULL);
	}
	buffer[fd] = ft_read(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(&buffer[fd]);
	if (!line && buffer[fd])
		(free(buffer[fd]), buffer[fd] = NULL);
	return (line);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	if (argc != 2)
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
