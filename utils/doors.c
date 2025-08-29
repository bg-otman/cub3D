/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:49:11 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/23 10:16:34 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_doors(char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	set_doors_pos(char **map, t_door **doors)
{
	int (i), (j), (k);
	i = 0;
	k = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				doors[k] = ft_malloc(sizeof(t_door));
				ft_bzero(doors[k], sizeof(t_door));
				doors[k]->is_closing = true;
				doors[k]->map_x = (j * TILE_SIZE);
				doors[k]->map_y = (i * TILE_SIZE);
				if (map[i][j - 1] == '1' && map[i][j + 1] == '1')
					doors[k]->is_horizontal = true;
				else
					doors[k]->is_horizontal = false;
				k++;
			}
			j++;
		}
		i++;
	}
}

bool	is_door(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = (x / TILE_SIZE);
	map_y = (y / TILE_SIZE);
	if (map_x < 0 || map_x >= (int)ft_strlen(data->map[map_y]))
		return (true);
	if (data->map[map_y][map_x] == 'D')
		return (true);
	return (false);
}

bool	is_door_close(t_data *data, int map_y, int map_x)
{
	t_door	*door;

	door = get_door_at(data, map_x, map_y);
	if (!door)
		return (false);
	if (door->progress < 1.00)
		return (true);
	return (false);
}

void	init_doors(t_data *data)
{
	data->doors_count = count_doors(data->map);
	if (data->doors_count == 0)
		return ;
	data->doors = ft_malloc(sizeof(t_door *) * data->doors_count + 1);
	data->doors[data->doors_count - 1] = NULL;
	set_doors_pos(data->map, data->doors);
}
