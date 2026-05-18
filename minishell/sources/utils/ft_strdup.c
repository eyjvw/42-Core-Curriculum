/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:19:02 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/04 00:43:15 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(char *str)
{
	char	*final;
	int		i;

	if (!str)
	{
		final = malloc(1);
		if (!final)
			return (NULL);
		final[0] = 0;
		return (final);
	}
	i = 0;
	final = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!final)
		return (NULL);
	while (str[i])
	{
		final[i] = str[i];
		i++;
	}
	final[i] = str[i];
	return (final);
}
