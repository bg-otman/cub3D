/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:00:12 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/22 15:56:01 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			; // this while will count min width
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
		put_error("Error\nsomething missing in map", data, false);
	}
	close(fd);
}

void	parse_map(t_data *data, char *av[])
{
	is_valid_file(*av, data);
	get_map_data(*av, data);
	// read_map(*av, data);
}
