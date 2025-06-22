/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:43:09 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/22 18:02:41 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_rotation(int key, t_data *data)
{
	t_player	*player;

	player = data->player;
	if (key == RIGHT)
		player->angle += player->rotation_speed;
	else if (key == LEFT)
		player->angle -= player->rotation_speed;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	else if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
	player->dx = cos(player->angle) * player->move_speed;
	player->dy = sin(player->angle) * player->move_speed;
}

int	mouse_rotate(int x, int y, t_data *data)
{
	int	center_x;
	int	delta;

	(void)y;
	center_x = WIN_WIDTH / 2;
	delta = x - center_x;
	if (delta == 0)
		return (0);
	data->player->angle += delta * (data->player->rotation_speed / 15);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, center_x, WIN_HEIGHT / 2);
	return (1);
}

void	get_wall_distance(t_data *data, t_dda *ray, double angle)
{
	if (ray->side == 0)
		ray->wall_dist = (double)((ray->map_x - data->player->x + (1
						- ray->step_x) / 2) / cos(angle));
	else
		ray->wall_dist = (double)((ray->map_y - data->player->y + (1
						- ray->step_y) / 2) / sin(angle));
}

void	draw_sky(t_data *data, double max_to_fill, int x)
{
	double			y;
	unsigned int	clr;

	clr = get_rgb_color(data->ceiling->r, data->ceiling->g, data->ceiling->b);
	y = 0;
	while (y < max_to_fill)
	{
		put_pixel_to_buffer(data->buffer, x, y, clr);
		y++;
	}
}

void	draw_floor(t_data *data, double floor_start, int x)
{
	double			y;
	unsigned int	clr;

	clr = get_rgb_color(data->floor->r, data->floor->g, data->floor->b);
	y = floor_start;
	while (y < WIN_HEIGHT)
	{
		put_pixel_to_buffer(data->buffer, x, y, clr);
		y++;
	}
}
