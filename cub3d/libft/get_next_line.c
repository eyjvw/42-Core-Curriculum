/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:13:54 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/19 18:33:58 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_rest(char *buffer, char *rest)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = ft_lento(buffer, '\n') + 1;
	if (!j)
		return (free(rest), NULL);
	len = ft_lento(&buffer[j], '\0');
	while (i < len)
		rest[i++] = buffer[j++];
	while (i < BUFFER_SIZE)
	{
		rest[i] = 0;
		i++;
	}
	return (rest);
}

//we assume buffer is malloced and needs to be free
char	*extract_line(char *full_line)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = -1;
	j = 0;
	len = ft_lento(full_line, '\n') + 1;
	if (!len)
		len = ft_lento(full_line, '\0');
	result = ft_calloc(sizeof(char), len + 1);
	if (!result)
		return (NULL);
	while (++i < len)
		result[i] = full_line[i];
	result[i] = 0;
	while (full_line[i])
		full_line[j++] = full_line[i++];
	while (full_line[j])
		full_line[j++] = 0;
	return (result);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*rest[FD_MAX];
	int			i;

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!rest[fd] || (!(ft_lento(buffer, '\n') + 1)
			&& !(ft_lento(rest[fd], '\n') + 1)))
	{
		i = 0;
		while (i < BUFFER_SIZE)
			buffer[i++] = 0;
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			return (kill_func(buffer, &rest[fd], i));
		rest[fd] = join_and_free(rest[fd], buffer);
		if (!rest[fd])
			return (free(buffer), NULL);
	}
	return (free(buffer), extract_line(rest[fd]));
}
