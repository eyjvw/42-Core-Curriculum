/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_row.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 03:07:00 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/11 20:58:15 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_replace_row(size_t id, char *new_row, char **strs)
{
	free(strs[id]);
	strs[id] = new_row;
	return (strs);
}
