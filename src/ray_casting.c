/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:53:57 by obouizi           #+#    #+#             */
/*   Updated: 2025/08/25 15:22:04 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_tex(t_texture tex, int x, t_data *data)
{
	int (y), (color), (tex_y);
	double (step), (tex_pos);
	if (tex.strip <= 0)
		tex.strip = 1;
	step = (double)tex.img->height / (double)tex.strip;
	tex_pos = (tex.first - (WIN_HEIGHT / 2.0) + (tex.strip / 2.0)) * step;
	draw_sky(data, tex.first, x);
	draw_floor(data, tex.last, x);
	y = tex.first;
	while (y <= tex.last)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex.img->height)
			tex_y = tex.img->height - 1;
		color = get_pixel_color(tex.img, tex.x, tex_y);
		put_pixel_to_buffer(data->buffer, x, y, color);
		tex_pos += step;
		y++;
	}
}

void	draw_textures(t_data *data, t_texture tex, int x, double angle)
{
	t_dda (*ray);
	ray = tex.ray;
	ray->wall_dist = ray->wall_dist * cos(angle - data->player->angle);
	tex.strip = (int)(WIN_HEIGHT / ray->wall_dist);
	tex.first = -tex.strip / 2 + WIN_HEIGHT / 2;
	if (tex.first < 0)
		tex.first = 0;
	tex.last = tex.strip / 2 + WIN_HEIGHT / 2;
	if (tex.last >= WIN_HEIGHT)
		tex.last = WIN_HEIGHT - 1;
	if (ray->side == 0)
		tex.hit_offset = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		tex.hit_offset = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
	tex.hit_offset -= floor(tex.hit_offset);
	tex.x = (int)(tex.hit_offset * tex.img->width);
	if (tex.x < 0)
		tex.x = 0;
	if (tex.x >= tex.img->width)
		tex.x = tex.img->width - 1;
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex.x = tex.img->width - tex.x - 1;
	draw_tex(tex, x, data);
}

void	implement_dda(t_dda *ray, t_data *data)
{
	ray->side = 0;
	while (data->map[ray->map_y][ray->map_x] != '1')
	{
		// if (is_door_blocking_ray(data, *ray))
		// 	return ;
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
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - ray->pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->wall_dist = (ray->map_y - ray->pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	ray_casting(t_data *data, double angle, int column_x)
{
	t_dda			ray;
	t_texture		tex;

	ray.pos_x = data->player->x / TILE_SIZE;
	ray.pos_y = data->player->y / TILE_SIZE;
	ray.map_x = (int)ray.pos_x;
	ray.map_y = (int)ray.pos_y;
	ray.ray_dir_x = cos(angle);
	if (ray.ray_dir_x == 0)
		ray.delta_dist_x = 1e30;
	else
		ray.delta_dist_x = fabs(1.0 / ray.ray_dir_x);
	ray.ray_dir_y = sin(angle);
	if (ray.ray_dir_y == 0)
		ray.delta_dist_y = 1e30;
	else
		ray.delta_dist_y = fabs(1.0 / ray.ray_dir_y);
	get_side_distance_and_step(&ray);
	implement_dda(&ray, data);
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
