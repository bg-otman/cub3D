/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:59:24 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/17 13:45:24 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*allocate_line(char *buffer)
{
	int		len;
	int		i;
	char	*ptr;

	if (!buffer)
		return (NULL);
	len = check_newline(buffer);
	if (len == -1)
		len = ft_slen(buffer);
	i = 0;
	ptr = (char *) ft_malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = buffer[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

ssize_t	read_data(int fd, char **buffer)
{
	ssize_t	bytes_read;

	if (fd < 0)
	{
		if (*buffer)
		{
			*buffer = NULL;
			return (-1);
		}
	}
	*buffer = (char *) ft_malloc(BUFFER_SIZE + 1);
	if (!*buffer)
		return (-1);
	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		*buffer = NULL;
		return (bytes_read);
	}
	(*buffer)[bytes_read] = '\0';
	return (bytes_read);
}

char	*allocate_and_free(char **buffer)
{
	char	*line;
	char	*temp;

	if (!buffer || !*buffer)
		return (NULL);
	line = allocate_line(*buffer);
	if (!line)
	{
		*buffer = NULL;
		return (NULL);
	}
	temp = ft_strdup(&(*buffer)[ft_slen(line)]);
	if (!temp)
	{
		*buffer = NULL;
		return (NULL);
	}
	*buffer = temp;
	return (line);
}

char	*get_last_line(char **buffer, ssize_t bytes_read)
{
	char	*line;

	if (bytes_read == -1)
	{
		*buffer = NULL;
		return (NULL);
	}
	if (*buffer && **buffer)
	{
		line = ft_strdup(*buffer);
		*buffer = NULL;
		return (line);
	}
	*buffer = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*ptr;
	char		*temp;
	ssize_t		byte_read;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (!buffer || fd < 0)
	{
		if (read_data(fd, &buffer) <= 0)
			return (NULL);
	}
	while (check_newline(buffer) == -1)
	{
		byte_read = read_data(fd, &temp);
		if (byte_read <= 0)
			return (get_last_line(&buffer, byte_read));
		ptr = ft_strjoin(buffer, temp);
		if (!ptr)
			return (NULL);
		buffer = ptr;
	}
	return (allocate_and_free(&buffer));
}
