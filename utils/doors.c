/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:49:11 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/16 18:52:29 by obouizi          ###   ########.fr       */
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
	int	i;
	int	j;
	int k;

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
	data->doors = ft_malloc(sizeof(t_door *) * data->doors_count + 1);
	data->doors[data->doors_count - 1] = NULL;
	set_doors_pos(data->map, data->doors);
}

void	check_nearby_doors(t_data *data, int *door_x, int *door_y)
{
    int	map_x;
    int	map_y;
	int num_blocks;

	num_blocks = 3;
	map_x = *door_x / TILE_SIZE;
	map_y = *door_y / TILE_SIZE;
	*door_x = map_x;
	*door_y = map_y;
    if (map_y - num_blocks > 0 && data->map[map_y - num_blocks][map_x] == 'D')
        *door_y = map_y - num_blocks;
    else if (map_y + num_blocks < data->map_height && data->map[map_y + num_blocks][map_x] == 'D')
        *door_y = map_y + num_blocks;
    else if (map_x - num_blocks > 0 && data->map[map_y][map_x - num_blocks] == 'D')
        *door_x = map_x - num_blocks;
    else if (map_x + num_blocks < data->map_width && data->map[map_y][map_x + num_blocks] == 'D')
        *door_x = map_x + num_blocks;
	else
	{
		*door_x = -1;
		*door_y = -1;
	}
}

t_door *get_door_at(t_data *data, int map_x, int map_y)
{
	int i;

	i = 0;
	while (i < data->doors_count)
	{
		if ((data->doors[i]->map_y / TILE_SIZE) == map_y
			&& (data->doors[i]->map_x / TILE_SIZE) == map_x)
			return (data->doors[i]);
		i++;
	}
	return (NULL);
}

bool	door_progress(t_data *data, t_dda ray)
{
	t_door	*door;
	double	hit_offset;
	double	fraction;

	door = get_door_at(data, ray.map_x / TILE_SIZE, ray.map_y / TILE_SIZE);
	if (!door)
		return (true);
	if (ray.side == 0)
		hit_offset = fmod(ray.map_y, TILE_SIZE);
	else
		hit_offset = fmod(ray.map_x, TILE_SIZE);
	fraction = hit_offset / TILE_SIZE;
	if (fraction >= 1.0 - door->progress)
		return (true);
	else
		return (false);
}


void	open_door(t_data *data, int plyr_x, int plyr_y)
{
	t_door *door;
	int	door_x;
	int	door_y;
	
	door_x = plyr_x;
	door_y = plyr_y;
	check_nearby_doors(data, &door_x, &door_y);
	if (door_x == -1 && door_y == -1)
		return ;
	door = get_door_at(data, door_x, door_y);
	if(door)
	{
		if (door->progress == 1.00)
		{
			door->is_closing = true;
			door->is_moving = true;
			door->is_opening = false;
		}
		else if (door->progress == 0.00)
		{
			door->is_closing = false;
			door->is_moving = true;
			door->is_opening = true;
		}
	}
}

void	update_doors(t_data *data, t_door **doors)
{
	int i;
	
	i = 0;
	while (i < data->doors_count)
	{
		if (doors[i]->is_opening)
		{
			doors[i]->progress += 0.01;
			if (doors[i]->progress >= 1.0)
			{
				doors[i]->progress = 1.0;
				doors[i]->is_opening = false;
				doors[i]->is_moving = false;
			}
		}
		else if (doors[i]->is_closing)
		{
			doors[i]->progress -= 0.01;
			if (doors[i]->progress <= 0.0)
			{
				doors[i]->progress = 0.0;
				doors[i]->is_closing = false;
				doors[i]->is_moving = false;
			}
		}
		i++;
	}
	
}
