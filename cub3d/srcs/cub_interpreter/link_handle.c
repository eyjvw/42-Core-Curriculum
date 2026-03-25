/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:17:55 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/19 01:15:52 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"

bool	check_link(const char *link, size_t line, t_data *data, int8_t id)
{
	int	fd;

	if (id == -1)
		return (false);
	fd = open(link, O_RDONLY);
	if (fd == -1)
		return (parse_error(INVALID, LINK, line), false);
	close (fd);
	data->texture_path[id] = ft_strdup(link);
	if (!data->texture_path[id])
		return (system_error(MALLOC), false);
	return (true);
}
