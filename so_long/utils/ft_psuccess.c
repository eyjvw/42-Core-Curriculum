/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_psuccess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 01:15:44 by sbonneau          #+#    #+#             */
/*   Updated: 2025/10/31 01:16:40 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_psuccess(const char *str)
{
	ft_putstr_fd(1, "[\033[32mSUCCESS\033[0m] ");
	ft_putstr_fd(1, str);
}
