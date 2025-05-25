/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:50:33 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/25 16:18:32 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_texture_path(char *tmp, t_data *data, int fd)
{
	char	**target;

	target = NULL;
	if (!ft_strncmp(tmp, "NO", 2) && !data->no_path)
		target = &data->no_path;
	else if (!ft_strncmp(tmp, "SO", 2) && !data->so_path)
		target = &data->so_path;
	else if (!ft_strncmp(tmp, "WE", 2) && !data->we_path)
		target = &data->we_path;
	else if (!ft_strncmp(tmp, "EA", 2) && !data->ea_path)
		target = &data->ea_path;
	else
	{
		close(fd);
		put_error("Error\nDuplicated identifier", data, false);
	}
	tmp += 2;
	if (!ft_isspace(*tmp))
	{
		close(fd);
		put_error("Error\nmissing space in identifier", data, false);
	}
	*target = ft_strtrim(tmp, WHITE_SPACES);
}

bool	is_valid_colors(const char *str)
{
	char	**colors;
	char	*tmp;

	int (i), (j);
	colors = ft_split(str, ',');
	i = 0;
	while (colors[i])
	{
		j = 0;
		tmp = ft_strtrim(colors[i], WHITE_SPACES);
		if (!tmp || !tmp[j])
			return (false);
		while (tmp[j])
			if (i > 2 || !ft_isdigit(tmp[j++]))
				return (false);
		i++;
	}
	if (i != 3)
		return (false);
	while (--i >= 0)
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			return (false);
	return (true);
}

void	set_colors(char *tmp, t_data *data, int fd)
{
	t_color	**target;
	char	**colors;

	target = NULL;
	if (tmp[0] == 'F' && !data->floor)
		target = &data->floor;
	else if (tmp[0] == 'C' && !data->ceiling)
		target = &data->ceiling;
	else
		(close(fd), put_error("Error\nDuplicated identifier", data, false));
	tmp += 1;
	if (!ft_isspace(*tmp))
		(close(fd), put_error("Error\nmissing space in identifier", data,
				false));
	tmp += skip_spacess(tmp);
	if (!is_valid_colors(tmp))
	{
		close(fd);
		put_error("Error\ninvalid color format", data, false);
	}
	*target = ft_malloc(sizeof(t_color));
	colors = ft_split(tmp, ',');
	(*target)->r = ft_atoi(colors[0]);
	(*target)->g = ft_atoi(colors[1]);
	(*target)->b = ft_atoi(colors[2]);
}

void	set_identifiers(char *line, int fd, t_data *data)
{
	if (ft_isspace(line[0]))
		line += skip_spacess(line);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		set_texture_path(line, data, fd);
	if (line[0] == 'F' || line[0] == 'C')
		set_colors(line, data, fd);
}

void	get_map_data(const char *map_path, t_data *data)
{
	int		fd;
	char	*tmp;
	int		offset;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		put_error("Error\nError opening map file : ", data, true);
	tmp = get_next_line(fd);
	offset = 0;
	while (tmp)
	{
		offset++;
		if (check_textures(tmp) == false)
			break ;
		set_identifiers(tmp, fd, data);
		if (data->ea_path && data->no_path && data->so_path
			&& data->we_path && data->floor && data->ceiling)
			break ;
		tmp = get_next_line(fd);
	}
	if (!(data->ea_path && data->no_path && data->so_path
			&& data->we_path && data->floor && data->ceiling))
		put_error("Error\nInvalid map", data, false);
	map_len(fd, data);
	read_map(map_path, offset, data);
}
