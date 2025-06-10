/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:53:57 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/10 14:53:57 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_strip(t_data *data, double len, int x)
{
	double	strip;
	double	first;
	double	last;

	strip = (TILE_SIZE / len) * ((WIN_WIDTH / 2) / tan(FOV / 2));
	first = (WIN_HEIGHT / 2) - (strip / 2);
	if (first < 0)
		first = 0;
	last = (WIN_HEIGHT / 2) + (strip / 2);
	if (last > WIN_HEIGHT)
		last = WIN_HEIGHT;
	while (first <= last)
	{
		put_pixel_to_buffer(data->buffer, x, first, 0xFFFFFF);
		first++;
	}
}

int	my_bool(bool condition, int yes, int no)
{
	if (condition)
		return (yes);
	return (no);
}

void	implement_dda(t_dda *ray, t_data *data, double angle)
{
	double (delta_dist_x), (delta_dist_y);
	delta_dist_x = fabs(1.0 / cos(angle));
	delta_dist_y = fabs(1.0 / sin(angle));
	while (!is_wall(data->map, ray->map_x, ray->map_y))
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += delta_dist_x;
			ray->map_x += (int)ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += delta_dist_y;
			ray->map_y += (int)ray->step_y;
			ray->side = 1;
		}
	}
}

void ray_casting(t_data *data, double angle, int column_x)
{
	t_dda	ray;

	ray.map_x = (int)floor(data->player->x);
	ray.map_y = (int)floor(data->player->y);
	ray.step_x = my_bool((cos(angle) < 0), -1, 1);
	ray.step_y = my_bool((sin(angle) < 0), -1, 1);
	ray.side_dist_x = (data->player->x - ray.map_x) * fabs(1.0 / cos(angle));
	if (ray.step_x > 0)
		ray.side_dist_x = ((ray.map_x + 1.0) - data->player->x) * fabs(1.0 / cos(angle));
	ray.side_dist_y = (data->player->y - ray.map_y) * fabs(1.0 / sin(angle));
	if (ray.step_y > 0)
		ray.side_dist_y = ((ray.map_y + 1.0) - data->player->y) * fabs(1.0 / sin(angle));
	ray.side = 0;
	implement_dda(&ray, data, angle);
	if (ray.side == 0)
		ray.wall_dist = (double)((ray.map_x - data->player->x + (1 - ray.step_x) / 2) / cos(angle));
	else
		ray.wall_dist = (double)((ray.map_y - data->player->y + (1 - ray.step_y) / 2) / sin(angle));
	draw_strip(data, ray.wall_dist, column_x);
}

void	field_of_view(t_data *data)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_casting(data, ((data->player->angle - (FOV / 2)) + (i * (FOV / NUM_RAYS))), i);
		i++;
	}
}
