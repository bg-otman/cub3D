/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:37:41 by obouizi           #+#    #+#             */
/*   Updated: 2024/11/08 19:13:36 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*node;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	node = ft_lstnew(f(lst->content));
	if (!node)
		return (NULL);
	newlst = node;
	lst = lst->next;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		node->next = temp;
		node = temp;
		lst = lst->next;
	}
	return (newlst);
}
