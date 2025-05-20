/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:42:25 by obouizi           #+#    #+#             */
/*   Updated: 2024/10/26 14:38:25 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char			*ptr_dst;
	const unsigned char		*ptr_src;
	size_t					i;

	ptr_dst = dst;
	ptr_src = src;
	i = 0;
	if (ptr_dst == ptr_src || n == 0)
		return (dst);
	while (i < n)
	{
		ptr_dst[i] = ptr_src[i];
		i++;
	}
	return (dst);
}
