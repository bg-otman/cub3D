/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:08:24 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/03 13:58:34 by obouizi          ###   ########.fr       */
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

int	clean_exit(t_data *data)
{
	if (!data)
		(free_garbage(), exit(EXIT_FAILURE));
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	//// here free ressources loaded by mlx's funs
	if (data->buffer)
	{
		if (data->buffer->img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->buffer->img_ptr);
		free(data->buffer);
	}
	/////
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_garbage();
	exit(data->exit_status);
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
				*x = MM_OFFSET_X + pos_x * TILE_SIZE;
				*y = MM_OFFSET_Y + pos_y * TILE_SIZE;
				*player_dir = map[pos_y][pos_x];
				break ;
			}
			pos_x++;
		}
		pos_y++;
	}
}
