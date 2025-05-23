/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:00:12 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/23 16:43:23 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
 * this function will just check if the map
 * meets the minimum dimension before procedding
 */
static bool	check_min_dimension(int fd)
{
	char	*tmp;
	int		height;
	int		width;

	tmp = get_next_line(fd);
	height = 0;
	width = 0;
	while (tmp)
	{
		height++;
		while (width < 6 && tmp[width++])
			;
		tmp = get_next_line(fd);
	}
	if (height < 11 || width < 6)
		return (false);
	return (true);
}

static void	is_valid_file(const char *map_path, t_data *data)
{
	int		fd;
	int		len;

	len = ft_strlen(map_path);
	if (len < 5 || ft_strncmp(&map_path[ft_strlen(map_path) - 4], ".cub", 4)
		|| map_path[len - 5] == '/')
		put_error("Error\nOnly valid \".cub\" map files are allowed!",
			data, false);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		put_error("Error\nError opening map file : ", data, true);
	if (!check_min_dimension(fd))
	{
		close(fd);
		put_error("Error\nsomething missing the in map", data, false);
	}
	close(fd);
}

static void	check_double_player(char c, bool *plyr_found, t_data *data)
{
	if (is_valid_char(c) && c != '0')
	{
		if (*plyr_found)
			put_error("Error\nOnly one player allowed", data, false);
		else
			*plyr_found = true;
	}
}

void	check_invalid_chars(char **map, t_data *data)
{
	bool	plyr_found;
	int		i;
	int		j;

	plyr_found = false;
	i = 1;
	while (i < data->map_height - 1)
	{
		j = 0;
		while (map[i][j])
		{
			check_double_player(map[i][j], &plyr_found, data);
			if (!ft_isspace(map[i][j]) && map[i][j] != '1'
				&& !is_valid_char(map[i][j]))
				put_error("Error\nInvalid character", data, false);
			j++;
		}
		i++;
	}
	if (!plyr_found)
		put_error("Error\nAt least one player required", data, false);
}

void	parse_map(t_data *data, char *av[])
{
	is_valid_file(*av, data);
	get_map_data(*av, data);
	check_walls(data->map, data);
	check_invalid_chars(data->map, data);
}
