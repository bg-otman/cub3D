/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:08:24 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/10 14:59:35 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_error(char *msg, t_data *data, bool sys_error)
{
	ft_putstr_fd(msg, 2);
	if (sys_error)
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	data->exit_status = EXIT_FAILURE;
	clean_exit(data);
}

bool	check_textures(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = skip_spacess(line);
	if (!line[i])
		return (true);
	if (!ft_strncmp("F", line, 1) || !ft_strncmp("C", line, 1))
	{
		i++;
		if (!ft_isspace(line[i]))
			return (false);
		return (true);
	}
	if (ft_strncmp("NO", line, 2) && ft_strncmp("SO", line, 2)
		&& ft_strncmp("WE", line, 2) && ft_strncmp("EA", line, 2))
		return (false);
	i += 2;
	if (!ft_isspace(line[i]))
		return (false);
	return (true);
}

void	get_player_pos(char **map, double	*x, double	*y, char *player_dir)
{
	int pos_x;
	int pos_y;
	
	pos_y = 0;
	while (map[pos_y])
	{
		pos_x = 0;
		while (map[pos_y][pos_x])
		{
			if (map[pos_y][pos_x] == 'N' || map[pos_y][pos_x] == 'W'
				|| map[pos_y][pos_x] == 'S' || map[pos_y][pos_x] == 'E')
			{
				*x = MM_OFFSET_X + (pos_x * TILE_SIZE) - PLAYER_SIZE;
				*y = MM_OFFSET_Y + (pos_y * TILE_SIZE) - PLAYER_SIZE;
				*player_dir = map[pos_y][pos_x];
				break ;
			}
			pos_x++;
		}
		pos_y++;
	}
}

unsigned int	get_rgb_color(int red, int green, int blue)
{
	return ((red << 16) + (green << 8) + blue);
}
