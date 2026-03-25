/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:06:15 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/15 16:55:00 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"

bool	check_missing(bool *dirs)
{
	uint8_t	i;
	bool	ret;

	i = 0;
	ret = true;
	while (i < 7)
	{
		if (dirs[i])
		{
			parse_error(MISSING, i, 0);
			ret = false;
		}
		i++;
	}
	return (ret);
}

int8_t	check_id(const char *id, size_t line, bool check_mod)
{
	size_t		i;
	static bool	dirs[7] = {true, true, true, true, true, true, true};
	const char	*dirs_s[7];

	i = 0;
	dirs_s[0] = "NO";
	dirs_s[1] = "SO";
	dirs_s[2] = "WE";
	dirs_s[3] = "EA";
	dirs_s[4] = "D";
	dirs_s[5] = "F";
	dirs_s[6] = "C";
	if (check_mod)
		return (check_missing(dirs));
	if (!id || !*id)
		return (-1);
	while (i < 7 && ((ft_strlen(dirs_s[i]) != ft_strlen(id))
			|| ft_strncmp(dirs_s[i], id, ft_strlen(dirs_s[i]))))
		i++;
	if (i == 7)
		return (parse_error(INVALID, ID, line), -1);
	if (dirs[i] == false)
		return (parse_error(DUPLICATE, i, line), -1);
	dirs[i] = false;
	return (i);
}
