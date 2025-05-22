/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:07:45 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/22 20:09:27 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_line_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}


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
				(close(fd), put_error("Error\nInvalid map",
				data, false));
			inside_map = true;
			if ((int) ft_strlen(line) > data->map_width)
				data->map_width = ft_strlen(line);
			data->map_height++;
		}
		line = get_next_line(fd);
	}
	close(fd);
}


// void	check_walls(char *line, int fd, t_data *data)
// {
// 	int		i;

// 	i = 0;
// 	// printf("line : {%s}\n", line);
// 	// while (line[0])
// 	// {
// 	// 	/* code */
// 	// }
	
// 	while (line && line[i])
// 	{
// 		if ((line[i] == '0' || line[i] == 'N'
// 			|| line[i] == 'S' || line[i] == 'E'
// 			|| line[i] == 'W') &&
// 			(line[i + 1] != '0' && line[i + 1] != 'N'
// 			&& line[i + 1] != 'S' && line[i + 1] != 'E'
// 			&& line[i + 1] != 'W' && line[i + 1] != '1'))
// 		{
// 			// printf("line[%d]  : {%c}  line[%d + 1] : {%c}  \n", i, line[i], i + 1, line[i + 1]);
// 			close(fd);
// 			put_error("Error\nInvalid map", data, false);
// 		}
// 		if (line[i] != '0' && line[i] != '1'
// 			&& line[i] != 'N' && line[i] != 'S'
// 			&& line[i] != 'E' && line[i] != 'W'
// 			&& !ft_isspace(line[i]))
// 		{
// 			close(fd);
// 			put_error("Error\nInvalid character", data, false);
// 		}
// 		i++;
// 	}
// }

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
		data->map[i++] = tmp;
		tmp = get_next_line(fd);
	}
	data->map[i] = NULL;
	close(fd);
}
