/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:01:23 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/21 17:09:37 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../../libft/libft.h"
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_slen(char const *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*get_last_line(char **buffer, ssize_t bytes_read);
char	*allocate_line(char *buffer);
int		check_newline(char *buffer);
ssize_t	read_data(int fd, char **buffer);
char	*allocate_and_free(char **buffer);

#endif
