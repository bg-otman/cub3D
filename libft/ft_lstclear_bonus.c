/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:33:45 by obouizi           #+#    #+#             */
/*   Updated: 2024/11/01 14:34:34 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		if ((*lst)->content)
			del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
