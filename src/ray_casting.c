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

void	draw_textures(t_data *data, t_dda *ray, int x)
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	line_height;
	double	tex_pos;
	int first, last;
	t_image *texture;

	if (ray->side == 0)
		texture = (ray->ray_dir_x > 0) ? data->we : data->ea;
	else
		texture = (ray->ray_dir_y > 0) ? data->no : data->so;
	line_height = (TILE_SIZE / ray->wall_dist) * ((WIN_WIDTH / 2) / tan(FOV / 2));
	first = fmax(0, (WIN_HEIGHT / 2) - (line_height / 2));
	last = fmin(WIN_HEIGHT, (WIN_HEIGHT / 2) + (line_height / 2));
	if (ray->side == 0)
		wall_x = data->player->y + ray->wall_dist * ray->ray_dir_y;
	else
		wall_x = data->player->x + ray->wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	if (tex_x < 0)
    	tex_x = 0;
	else if (tex_x >= texture->width)
    	tex_x = texture->width - 1;
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	step = (double)texture->height / line_height;
	tex_pos = (first - WIN_HEIGHT/2 + line_height/2) * step;
	while (first < last)
	{
		tex_y = (int)tex_pos % texture->height;
		if (tex_y < 0)
    		tex_y += texture->height;
		put_pixel_to_buffer(data->buffer, x, first, get_pixel_color(texture, tex_x, tex_y));
		tex_pos += step;
		first++;
	}
}


void	draw_strip(t_data *data, double len, int x, t_texture tex, double angle)
{
	double	strip;
	double	first;
	double	last;

	len = len * cos(angle - data->player->angle);
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

void	implement_dda(t_dda *ray, t_data *data)
{
	while (!is_wall(data, ray->map_x, ray->map_y))
	{
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

void ray_casting(t_data *data, double angle, int column_x)
{
	t_dda	ray;
	t_door *door;
	t_texture tex;

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
		ray.side_dist_x = ((ray.map_x + 1.0) - data->player->x) * ray.delta_dist_x;
	ray.side_dist_y = (data->player->y - ray.map_y) * ray.delta_dist_y;
	if (ray.step_y > 0)
		ray.side_dist_y = ((ray.map_y + 1.0) - data->player->y) * ray.delta_dist_y;
	ray.side = 0;
	implement_dda(&ray, data);
	if (ray.side == 0)
		ray.wall_dist = (double)((ray.map_x - data->player->x + (1 - ray.step_x) / 2) / cos(angle));
	else
		ray.wall_dist = (double)((ray.map_y - data->player->y + (1 - ray.step_y) / 2) / sin(angle));
	tex.ray = &ray;
	if (ray.side == 0)
		tex.img = (ray.ray_dir_x > 0) ? data->we : data->ea;
	else
		tex.img = (ray.ray_dir_y > 0) ? data->no : data->so;
	door = get_door_at(data, ray.map_x / TILE_SIZE, ray.map_y / TILE_SIZE);
	if (door)
		tex.img = data->door_img;
	draw_strip(data, ray.wall_dist, column_x, tex, angle);
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
