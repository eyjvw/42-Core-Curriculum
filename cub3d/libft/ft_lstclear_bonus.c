/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:15:06 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/27 21:15:07 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev;

	prev = NULL;
	while ((*lst) != NULL)
	{
		del((*lst)->content);
		prev = (*lst);
		(*lst) = (*lst)->next;
		free(prev);
	}
}
