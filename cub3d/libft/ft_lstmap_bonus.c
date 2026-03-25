/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:15:32 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/27 21:15:32 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newelem;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	newlist = NULL;
	while (lst != NULL)
	{
		content = f(lst->content);
		if (!content)
			return (ft_lstclear(&newlist, del), NULL);
		newelem = ft_lstnew(content);
		if (!newelem)
			return (del(content), ft_lstclear(&newlist, del), NULL);
		ft_lstadd_back(&newlist, newelem);
		lst = lst->next;
	}
	return (newlist);
}
