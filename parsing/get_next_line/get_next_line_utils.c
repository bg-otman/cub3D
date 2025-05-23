/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:00:27 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/21 12:18:41 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_slen(char const *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

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

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_slen(s1);
	ptr = (char *) ft_malloc(s_len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < s_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[s_len] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_slen(s1);
	s2_len = ft_slen(s2);
	ptr = (char *) ft_malloc((s1_len + s2_len) + 1);
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, s1_len);
	ft_memcpy(ptr + s1_len, s2, s2_len);
	ptr[s1_len + s2_len] = '\0';
	return (ptr);
}

int	check_newline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (++i);
		i++;
	}
	return (-1);
}
