/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_identifiers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:50:33 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/21 19:53:09 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_texture_path(char *tmp, t_data *data, int fd)
{
	char	**target;

	target = NULL;
	if (!ft_strncmp(tmp, "NO", 2))
		target = &data->no_path;
	else if (!ft_strncmp(tmp, "SO", 2))
		target = &data->so_path;
	else if (!ft_strncmp(tmp, "WE", 2))
		target = &data->we_path;
	else
		target = &data->ea_path;
	tmp += 2;
	if (!ft_isspace(*tmp))
	{
		close(fd);
		put_error("Error\nmissing space in identifier", data, false);
	}
	tmp += skip_spacess(tmp);
	*target = ft_strtrim(tmp, "\n");
}

bool	is_valid_colors(const char *str)
{
	char	**colors;
	int		i;
	int		j;

	colors = ft_split(str, ',');
	i = 0;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
		{
			if (i > 2 || (!(colors[i][j] >= '0' && colors[i][j] <= '9')
				&& colors[i][j] != ',' && colors[i][j] != '\n'
				&& !ft_isspace(colors[i][j])))
				return (false);
			j++;
		}
		i++;
	}
	while (--i > 0)
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			return (false);
	return (true);
}

void	set_colors(char *tmp, t_data *data, int fd)
{
	t_color	*target;
	char	**colors;

	target = NULL;
	if (tmp[0] == 'F')
		target = &data->floor;
	else
		target = &data->ceiling;
	tmp += 1;
	if (!ft_isspace(*tmp))
	{
		close(fd);
		put_error("Error\nmissing space in identifier", data, false);
	}
	tmp += skip_spacess(tmp);
	if (!is_valid_colors(tmp))
	{
		close(fd);
		put_error("Error\ninvalid color format", data, false);
	}
	colors = ft_split(tmp, ',');
	target->r = ft_atoi(colors[0]);
	target->g = ft_atoi(colors[1]);
	target->b = ft_atoi(colors[2]);
}

void	set_identifiers(const char *map_path, t_data *data)
{
	int		fd;
	char	*tmp;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		put_error("Error\nError opening map file : ", data, true);
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (ft_isspace(tmp[0]))
			tmp += skip_spacess(tmp);
		if (!ft_strncmp(tmp, "NO", 2) || !ft_strncmp(tmp, "SO", 2)
			|| !ft_strncmp(tmp, "WE", 2) || !ft_strncmp(tmp, "EA", 2))
			set_texture_path(tmp, data, fd);
		if (tmp[0] == 'F' || tmp[0] == 'C')
			set_colors(tmp, data, fd);
		tmp = get_next_line(fd);
	}
	close(fd);
}
