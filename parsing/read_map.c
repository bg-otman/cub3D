/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:07:45 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/23 16:49:44 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_len(int fd, t_data *data)
{
	char	*line;
	bool	inside_map;
	bool	found_gap;

	inside_map = false;
	found_gap = false;
	line = get_next_line(fd);
	while (line)
	{
		if (inside_map && is_line_empty(line))
			found_gap = true;
		if (!is_line_empty(line))
		{
			if (found_gap)
				(close(fd), put_error("Error\nInvalid map", data, false));
			inside_map = true;
			if ((int)ft_strlen(line) > data->map_width)
				data->map_width = ft_strlen(line);
			data->map_height++;
		}
		line = get_next_line(fd);
	}
	close(fd);
}

void	check_is_surrounded(char *last, char *curr, char *next, t_data *data)
{
	int	i;

	i = 0;
	while (curr[i])
	{
		if ((is_valid_char(curr[i]) && (ft_isspace(last[i])
					|| ft_isspace(next[i]))) || (is_valid_char(curr[i])
				&& ft_isspace(curr[i + 1]))
				|| (ft_isspace(curr[i]) && is_valid_char(curr[i + 1])))
			put_error("Error\nInvalid map", data, false);
		i++;
	}
}

void	check_walls(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[0][i])
	{
		if (map[0][i] != '1' && !ft_isspace(map[0][i]))
			put_error("Error\nInvalid map", data, false);
		i++;
	}
	i = 1;
	while (i < data->map_height - 1)
	{
		check_is_surrounded(map[i - 1], map[i], map[i + 1], data);
		i++;
	}
	j = 0;
	while (map && map[i][j])
	{
		if (map[i][j] != '1' && !ft_isspace(map[i][j]))
			put_error("Error\nInvalid map", data, false);
		j++;
	}
}

char	*add_padding(char *line, int space_num)
{
	char	*padded_line;
	bool	has_newline;

	int (len), (i);
	has_newline = false;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
	{
		has_newline = true;
		len--;
	}
	if (has_newline)
		padded_line = ft_malloc(len + space_num + 2);
	else
		padded_line = ft_malloc(len + space_num + 1);
	i = -1;
	while (++i < len)
		padded_line[i] = line[i];
	while (space_num-- > 0)
		padded_line[i++] = ' ';
	if (has_newline)
		padded_line[i++] = '\n';
	padded_line[i] = '\0';
	return (padded_line);
}

void	read_map(const char *map_path, int offset, t_data *data)
{
	int		fd;
	char	*tmp;
	int		i;

	data->map = ft_malloc(sizeof(char *) * (data->map_height + 1));
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		put_error("Error\nError opening map file : ", data, true);
	while (offset-- >= 0 || is_line_empty(tmp))
		tmp = get_next_line(fd);
	i = 0;
	while (tmp && !is_line_empty(tmp))
	{
		if ((int)ft_strlen(tmp) != data->map_width)
			tmp = add_padding(tmp, data->map_width - ft_strlen(tmp));
		data->map[i++] = tmp;
		tmp = get_next_line(fd);
	}
	data->map[i] = NULL;
	close(fd);
}
