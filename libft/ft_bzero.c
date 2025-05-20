/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:09:53 by obouizi           #+#    #+#             */
/*   Updated: 2024/11/04 12:24:24 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	if (n == 0)
		return ;
	i = 0;
	ptr = (unsigned char *) s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
