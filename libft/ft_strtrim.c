/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:19:26 by obouizi           #+#    #+#             */
/*   Updated: 2024/10/27 11:27:26 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_findstartset(const char *s1, const char *set)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
			{
				count++;
				break ;
			}
			j++;
		}
		if (set[j] != s1[i])
			break ;
		i++;
	}
	return (count);
}

static	size_t	ft_findendset(const char *s1, const char *set)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = ft_strlen(s1) - 1;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
			{
				count++;
				break ;
			}
			j++;
		}
		if (set[j] != s1[i])
			break ;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	s1_len;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	start = ft_findstartset(s1, set);
	end = ft_findendset(s1, set);
	ptr = ft_substr(s1, start, s1_len - (start + end));
	return (ptr);
}
