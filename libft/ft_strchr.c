/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:02:22 by obouizi           #+#    #+#             */
/*   Updated: 2024/11/04 15:47:48 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	char	ch;

	ptr = (char *) s;
	ch = (char) c;
	while (*ptr)
	{
		if (*ptr == ch)
			return (ptr);
		ptr++;
	}
	if (*ptr == ch)
		return (ptr);
	return (0);
}
