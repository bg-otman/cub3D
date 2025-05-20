/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:07:33 by obouizi           #+#    #+#             */
/*   Updated: 2024/11/02 15:55:48 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *) haystack);
	i = 0;
	while ((i < len) && haystack[i])
	{
		j = 0;
		while (needle[j] && needle[j] == haystack[i + j] && (i + j) < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)(&haystack[i]));
		i++;
	}
	return (NULL);
}
