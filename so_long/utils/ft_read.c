/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 04:12:45 by sbonneau          #+#    #+#             */
/*   Updated: 2025/10/30 06:45:46 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_read(const int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*data;
	char	*temp;
	long	bytes;

	data = malloc(sizeof(char));
	if (!data)
		return (NULL);
	data[0] = '\0';
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes < 0)
			return (free(data), NULL);
		buffer[bytes] = '\0';
		temp = ft_strjoin(data, buffer);
		if (!temp)
			return (free(data), NULL);
		free(data);
		data = temp;
	}
	return (data);
}
