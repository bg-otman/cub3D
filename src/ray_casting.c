/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:53:57 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/17 19:24:04 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	draw_strip(t_data *data, double len, int x, int color)
// {
// 	double	strip;
// 	double	first;
// 	double	last;

// 	strip = (TILE_SIZE / len) * ((WIN_WIDTH / 2) / tan(FOV / 2));
// 	first = (WIN_HEIGHT / 2) - (strip / 2);
// 	if (first < 0)
// 		first = 0;
// 	last = (WIN_HEIGHT / 2) + (strip / 2);
// 	if (last > WIN_HEIGHT)
// 		last = WIN_HEIGHT;
// 	draw_sky(data, first, x);
// 	draw_floor(data, last, x);
// 	while (first <= last)
// 	{
// 		put_pixel_to_buffer(data->buffer, x, first, color);
// 		first++;
// 	}
// }

void	draw_strip(t_data *data, double len, int x, t_texture tex)
{
	double	strip;
	double	first;
	double	last;

	if (tex.ray->side != 0)
		tex.hit_offset = fmod(tex.ray->map_x, TILE_SIZE);
	else
		tex.hit_offset = fmod(tex.ray->map_y, TILE_SIZE);
	tex.x = ((tex.hit_offset / TILE_SIZE) * tex.img->width);
	if (tex.x < 0 || tex.x >= tex.img->width)
		return;
	strip = (TILE_SIZE / len) * ((WIN_WIDTH / 2) / tan(FOV / 2));
	first = (WIN_HEIGHT / 2) - (strip / 2);
	if (first < 0)
		first = 0;
	last = (WIN_HEIGHT / 2) + (strip / 2);
	if (last > WIN_HEIGHT)
		last = WIN_HEIGHT;
	draw_sky(data, first, x);
	draw_floor(data, last, x);
	tex.draw_start = first;
	while (first <= last)
	{
		tex.ratio = (first - tex.draw_start) / strip;
		tex.y = tex.ratio * tex.img->height;
		if (tex.y < 0)
			tex.y = 0;
		else if (tex.y >= tex.img->height)
			tex.y = tex.img->height - 1;
		put_pixel_to_buffer(data->buffer, x, first,
			get_pixel_color(tex.img, tex.x, tex.y));
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
	while (!is_wall(data, ray->map_x, ray->map_y) || is_door(data, ray->map_x, ray->map_y))
	{
		if (is_door(data, ray->map_x, ray->map_y)
			&& !is_door_blocking_ray(data, *ray))
			return ;
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
	t_door *door;
	t_texture tex;

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
	tex.ray = &ray;
	tex.img = data->wall_img;
	door = get_door_at(data, ray.map_x / TILE_SIZE, ray.map_y / TILE_SIZE);
	if (door)
	{
		tex.img = data->door_img;
		draw_strip(data, ray.wall_dist, column_x, tex);
	}
	else
		draw_strip(data, ray.wall_dist, column_x, tex);
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
