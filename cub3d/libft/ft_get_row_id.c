/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_row_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 03:06:40 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/18 04:31:19 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_row_id(char *content, char **strs)
{
	int	row;

	row = 0;
	while (strs[row] && ft_strncmp(strs[row], content, ft_strlen(content)))
		row++;
	if (strs[row])
		return (row);
	return (-1);
}
