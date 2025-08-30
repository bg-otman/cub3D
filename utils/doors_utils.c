/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:35:24 by obouizi           #+#    #+#             */
/*   Updated: 2025/08/25 15:22:24 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	find_nearby_door(t_data *data, int *door_x, int *door_y, int range)
{
	int	map_x;
	int	map_y;

	map_x = *door_x / TILE_SIZE;
	map_y = *door_y / TILE_SIZE;
	*door_x = map_x;
	*door_y = map_y;
	if (map_y - range > 0 && data->map[map_y - range][map_x] == 'D')
		*door_y = map_y - range;
	else if (map_y + range < data->map_height && data->map[map_y
			+ range][map_x] == 'D')
		*door_y = map_y + range;
	else if (map_x - range > 0 && data->map[map_y][map_x - range] == 'D')
		*door_x = map_x - range;
	else if (map_x + range < data->map_width && data->map[map_y][map_x
		+ range] == 'D')
		*door_x = map_x + range;
	else
		return (false);
	return (true);
}

t_door	*get_door_at(t_data *data, int map_x, int map_y)
{
	int	i;

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

bool	is_door_blocking_ray(t_data *data, t_dda ray)
{
	t_door	*door;
	double	hit_offset;
	double	t;

	double (hit_x_px), (hit_y_px);
	if (ray.side == 0)
		t = (ray.map_x - ray.pos_x + (1 - ray.step_x) / 2.0) / ray.ray_dir_x;
	else
		t = (ray.map_y - ray.pos_y + (1 - ray.step_y) / 2.0) / ray.ray_dir_y;
	hit_x_px = (ray.pos_x + (ray.ray_dir_x * t)) * TILE_SIZE;
	hit_y_px = (ray.pos_y + (ray.ray_dir_y * t)) * TILE_SIZE;
	door = get_door_at(data, ray.map_x, ray.map_y);
	if (!door)
		return (false);
	if (door->is_horizontal)
		hit_offset = fmod(hit_x_px, TILE_SIZE) / TILE_SIZE;
	else
		hit_offset = fmod(hit_y_px, TILE_SIZE) / TILE_SIZE;
	if (hit_offset >= 1.0 - door->progress)
		return (true);
	return (false);
}

void	open_door(t_data *data, int plyr_x, int plyr_y)
{
	t_door	*door;

	int (door_x), (door_y), (range);
	door_x = plyr_x;
	door_y = plyr_y;
	range = 1;
	while (range < 4 && !find_nearby_door(data, &door_x, &door_y, range++))
	{
		door_x = plyr_x;
		door_y = plyr_y;
	}
	door = get_door_at(data, door_x, door_y);
	if (range <= 4 && door && door->progress == 1.00 && data->map[(plyr_y
				+ PLAYER_SIZE) / TILE_SIZE][plyr_x / TILE_SIZE] != 'D'
		&& data->map[plyr_y / TILE_SIZE][(plyr_x + PLAYER_SIZE)
		/ TILE_SIZE] != 'D')
	{
		door->is_closing = true;
		door->is_opening = false;
	}
	else if (range <= 4 && door && door->progress == 0.00)
	{
		door->is_closing = false;
		door->is_opening = true;
	}
}

void	update_doors(t_data *data, t_door **doors)
{
	int	i;

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
			}
		}
		else if (doors[i]->is_closing)
		{
			doors[i]->progress -= 0.01;
			if (doors[i]->progress <= 0.0)
			{
				doors[i]->progress = 0.0;
				doors[i]->is_closing = false;
			}
		}
		i++;
	}
}
