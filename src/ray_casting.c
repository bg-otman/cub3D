/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:53:57 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/21 21:00:06 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_tex(t_texture tex, int x, t_data *data)
{
	while (tex.first < tex.last)
	{
		tex.y = (int)tex.pos % tex.img->height;
		if (tex.y < 0)
			tex.y += tex.img->height;
		put_pixel_to_buffer(data->buffer, x, tex.first, get_pixel_color(tex.img,
				tex.x, tex.y));
		tex.pos += tex.img->height / tex.strip;
		tex.first++;
	}
}

void	draw_textures(t_data *data, t_texture tex, int x, double angle)
{
	tex.ray->wall_dist = tex.ray->wall_dist * cos(angle - data->player->angle);
	tex.strip = (TILE_SIZE / tex.ray->wall_dist) * ((WIN_WIDTH / 2) / tan(FOV
				/ 2));
	tex.first = fmax(0, (WIN_HEIGHT / 2) - (tex.strip / 2));
	tex.last = fmin(WIN_HEIGHT, (WIN_HEIGHT / 2) + (tex.strip / 2));
	if (tex.ray->side != 0)
		tex.hit_offset = fmod(tex.ray->map_x, TILE_SIZE);
	else
		tex.hit_offset = fmod(tex.ray->map_y, TILE_SIZE);
	tex.x = ((tex.hit_offset / TILE_SIZE) * tex.img->width);
	if (tex.x < 0)
		tex.x = 0;
	else if (tex.x >= tex.img->width)
		tex.x = tex.img->width - 1;
	if ((tex.ray->side == 0 && tex.ray->ray_dir_x < 0) || (tex.ray->side == 1
			&& tex.ray->ray_dir_y > 0))
		tex.x = tex.img->width - tex.x - 1;
	tex.pos = (tex.first - WIN_HEIGHT / 2 + tex.strip / 2) * (tex.img->height
			/ tex.strip);
	draw_sky(data, tex.first, x);
	draw_floor(data, tex.last, x);
	draw_tex(tex, x, data);
}

void	implement_dda(t_dda *ray, t_data *data)
{
	ray->side = 0;
	while (!is_wall(data, ray->map_x, ray->map_y) || is_door(data, ray->map_x,
			ray->map_y))
	{
		if (is_door(data, ray->map_x, ray->map_y) && !is_door_blocking_ray(data,
				*ray))
			return ;
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

void	ray_casting(t_data *data, double angle, int column_x)
{
	t_dda		ray;
	t_texture	tex;

	ray.ray_dir_x = cos(angle);
	ray.ray_dir_y = sin(angle);
	ray.delta_dist_x = fabs(1.0 / ray.ray_dir_x);
	ray.delta_dist_y = fabs(1.0 / ray.ray_dir_y);
	ray.map_x = floor(data->player->x);
	ray.map_y = floor(data->player->y);
	ray.step_x = my_bool((ray.ray_dir_x < 0), -1, 1);
	ray.step_y = my_bool((ray.ray_dir_y < 0), -1, 1);
	ray.side_dist_x = (data->player->x - ray.map_x) * ray.delta_dist_x;
	if (ray.step_x > 0)
		ray.side_dist_x = ((ray.map_x + 1.0) - data->player->x)
			* ray.delta_dist_x;
	ray.side_dist_y = (data->player->y - ray.map_y) * ray.delta_dist_y;
	if (ray.step_y > 0)
		ray.side_dist_y = ((ray.map_y + 1.0) - data->player->y)
			* ray.delta_dist_y;
	implement_dda(&ray, data);
	get_wall_distance(data, &ray, angle);
	tex.ray = &ray;
	tex.img = get_tex_img(data, tex);
	draw_textures(data, tex, column_x, angle);
}

void	field_of_view(t_data *data)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_casting(data, ((data->player->angle - (FOV / 2)) + (i * (FOV
						/ NUM_RAYS))), i);
		i++;
	}
}
