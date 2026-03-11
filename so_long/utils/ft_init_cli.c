/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cli.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 04:10:36 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/02 07:49:21 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**get_ascii(void)
{
	int		fd;
	char	*buffer;
	char	**ascii;

	fd = open("cli/so_long.txt", O_RDONLY);
	if (fd == -1)
		return (NULL);
	buffer = ft_read(fd);
	if (!buffer)
		return (NULL);
	ascii = ft_split(buffer, '\n');
	if (!ascii)
		return (NULL);
	free(buffer);
	close(fd);
	return (ascii);
}

void	ft_init_cli(void)
{
	int		i;
	char	**ascii;

	i = 0;
	ascii = get_ascii();
	ft_clear_fd(1);
	if (ascii)
	{
		while (ascii[i])
		{
			if (ascii[i])
			{
				ft_putstr_fd(1, ascii[i]);
				ft_putstr_fd(1, "\n");
				free(ascii[i]);
			}
			i++;
		}
		free(ascii);
	}
}
