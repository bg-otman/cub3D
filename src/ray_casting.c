#include "../cub3d.h"

void	draw_textures(t_data *data, t_dda *ray, double angle, int x)
{
	double	hit_coord;
	double	wall_x;
	double	tex_x;
	double	step;
	double	line_height;
	double	tex_pos;
	int first, last, tex_y;

	line_height = (TILE_SIZE / ray->wall_dist) * ((WIN_WIDTH / 2) / tan(FOV / 2));
	first = (WIN_HEIGHT / 2) - (line_height / 2);
	if (first < 0)
		first = 0;
	last = (WIN_HEIGHT / 2) + (line_height / 2);
	if (last > WIN_HEIGHT)
		last = WIN_HEIGHT;
	hit_coord = data->player->x + ray->wall_dist * cos(angle);
	if (ray->side)
		hit_coord = data->player->y + ray->wall_dist * sin(angle);
	wall_x = hit_coord - floor(hit_coord);
	tex_x = floor(wall_x * TEXTURE_WIDTH);
	if ((ray->side == 0 && cos(angle) > 0) || (ray->side == 1 && sin(angle) < 0))
		tex_x = TEXTURE_WIDTH - tex_x - 1;
	step = (double)TEXTURE_HEIGHT / line_height;
	tex_pos = (first - WIN_HEIGHT / 2 + line_height / 2) * step;
	for (int y = first; y < last; y++)
	{
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		put_pixel_to_buffer(data->buffer, x, y, get_pixel_color(data->texture, tex_x, tex_y));
		tex_pos += step;
	}
}

double	my_bool(bool condition, double yes, double no)
{
	if (condition)
		return (yes);
	return (no);
}

void	implement_dda(t_dda *ray, t_data *data)
{
	while (!is_wall(data->map, ray->map_x, ray->map_y))
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
	t_dda			ray;

	ray.delta_dist_x = fabs(1.0 / cos(angle));
	ray.delta_dist_y = fabs(1.0 / sin(angle));
	ray.map_x = floor(data->player->x);
	ray.map_y = floor(data->player->y);
	ray.step_x = my_bool((cos(angle) < 0), -1, 1);
	ray.step_y = my_bool((sin(angle) < 0), -1, 1);
	ray.side_dist_x = (data->player->x - ray.map_x) * ray.delta_dist_x;
	if (ray.step_x > 0)
		ray.side_dist_x = ((ray.map_x + 1.0) - data->player->x) * ray.delta_dist_x;
	ray.side_dist_y = (data->player->y - ray.map_y) * ray.delta_dist_y;
	if (ray.step_y > 0)
		ray.side_dist_y = ((ray.map_y + 1.0) - data->player->y) * ray.delta_dist_y;
	ray.side = 0;
	implement_dda(&ray, data);
	if (ray.side == 0)
		ray.wall_dist = ((ray.map_x - data->player->x + (1 - ray.step_x) / 2) / cos(angle));
	else
		ray.wall_dist = ((ray.map_y - data->player->y + (1 - ray.step_y) / 2) / sin(angle));
	ray.wall_dist = fabs(ray.wall_dist);
	draw_textures(data, &ray, angle, column_x);
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
