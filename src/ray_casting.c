#include "../cub3d.h"

void	draw_wall(int x, int draw_start, int draw_end, t_image *img)
{
	int	y;

	if (draw_start < 0)
		draw_start = 0;
	if (draw_end > WIN_HEIGHT)
		draw_end = WIN_HEIGHT;
	y = draw_start;
	while (y < draw_end)
	{
		put_pixel_to_buffer(img, x, y, 0xFFFFFF);
		y++;
	}
}

void	render_walls(double ray_len, int ray_index, t_image *img)
{
	int	dist_projection;
	int	line_height;
	int	draw_start;
	int	draw_end;

	if (ray_len <= 0)
		ray_len = 1;
	dist_projection = (WIN_WIDTH / 2) / tan(FOV / 2);
	line_height = (TILE_SIZE / ray_len) * dist_projection;
	draw_start = (WIN_HEIGHT / 2) - (line_height / 2);
	draw_end = draw_start + line_height;
	draw_wall(ray_index, draw_start, draw_end, img);
}

/*
* * *  casting rays with the normal way * * *
*/
int	cast_ray(t_data *data, int x, int y, double angle)
{
	double	current_x;
	double	current_y;
	int		i;
	int		len;

	len = WIN_WIDTH;
	i = 0;
	while (i < len)
	{
		current_x = x + cos(angle) * i;
		current_y = y + sin(angle) * i;
		if (data->map_height >= (current_y / TILE_SIZE) && is_wall(data->map,
				current_x, current_y))
			break ;
		i++;
	}
	return (fabs(current_y - y));
}

void	field_of_view(t_data *data, t_player *player)
{
	double	angle_step;
	double	start_angle;
	double	ray_angle;
	double	ray_len;
	int		i;

	angle_step = (FOV / NUM_RAYS);
	start_angle = player->angle - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + (i * angle_step);
		ray_len = cast_ray(data, player->x + PLAYER_SIZE / 2, player->y
				+ PLAYER_SIZE / 2, ray_angle);
		render_walls(ray_len, i, data->buffer);
		i++;
	}
}
