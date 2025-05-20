/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:43:25 by obouizi           #+#    #+#             */
/*   Updated: 2024/10/24 11:26:46 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*ptr_dst;
	const unsigned char		*ptr_src;
	size_t					i;

	ptr_dst = dst;
	ptr_src = src;
	i = 0;
	if (ptr_dst == ptr_src || len == 0)
		return (dst);
	if (ptr_dst < ptr_src)
	{
		while (i < len)
		{
			ptr_dst[i] = ptr_src[i];
			i++;
		}
	}
	else if (ptr_dst > ptr_src)
	{
		while (len-- > 0)
		{
			ptr_dst[len] = ptr_src[len];
		}
	}
	return (dst);
}
