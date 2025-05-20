/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:19:05 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/20 18:59:07 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_grbg_collector	**get_gc(void)
{
	static t_grbg_collector	*gc;

	return (&gc);
}

void	track_allocation(void *ptr)
{
	t_grbg_collector	**gc;
	t_grbg_collector	*tmp;

	gc = get_gc();
	if (!*gc)
	{
		*gc = malloc(sizeof(t_grbg_collector));
		if (!*gc)
			return ;
		(*gc)->ptr = ptr;
		(*gc)->next = NULL;
	}
	else
	{
		tmp = *gc;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_grbg_collector));
		if (!tmp->next)
			return ;
		tmp->next->ptr = ptr;
		tmp->next->next = NULL;
	}
}

void	free_garbage(void)
{
	t_grbg_collector	**gc;
	t_grbg_collector	*tmp;

	gc = get_gc();
	while (*gc)
	{
		tmp = (*gc)->next;
		if ((*gc)->ptr)
			free((*gc)->ptr);
		if (*gc)
			free(*gc);
		*gc = tmp;
	}
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (perror("Allocation fails"), free_garbage(), exit(1), NULL);
	track_allocation(ptr);
	return (ptr);
}
