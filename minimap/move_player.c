/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:10:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/29 14:56:59 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_wall(char **map, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = (x / TILE_SIZE) - 1;
	map_y = (y / TILE_SIZE) - 1;
	if (map_y < 0 || !map[map_y])
		return (true);
	if (map_x < 0 || map_x >= (int)ft_strlen(map[map_y]))
		return (true);
	if (map[map_y][map_x] == '1')
		return (true);
	return (false);
}

void	horizontal_moves(int key, t_data *data)
{
	int	speed;

	speed = data->player->move_speed;
	if (key == D_KEY)
	{
		if (!(is_wall(data->map, data->player->x + speed + PLAYER_SIZE - 1,
					data->player->y) || is_wall(data->map, data->player->x
					+ speed + PLAYER_SIZE - 1, data->player->y + PLAYER_SIZE
					- 1)))
			data->player->x += speed;
	}
	else if (key == A_KEY)
	{
		if (!(is_wall(data->map, data->player->x - speed, data->player->y)
				|| is_wall(data->map, data->player->x - speed, data->player->y
					+ PLAYER_SIZE - 1)))
			data->player->x -= speed;
	}
}

void	vertical_moves(int key, t_data *data)
{
	int	speed;

	speed = data->player->move_speed;
	if (key == S_KEY)
	{
		if (!(is_wall(data->map, data->player->x, data->player->y + speed
					+ PLAYER_SIZE - 1) || is_wall(data->map, data->player->x
					+ PLAYER_SIZE - 1, data->player->y + speed + PLAYER_SIZE
					- 1)))
			data->player->y += speed;
	}
	else if (key == W_KEY)
	{
		if (!(is_wall(data->map, data->player->x, data->player->y - speed)
				|| is_wall(data->map, data->player->x + PLAYER_SIZE - 1,
					data->player->y - speed)))
			data->player->y -= speed;
	}
}

void	rotate_player(int key, t_data *data)
{
	if (key == RIGHT)
		data->player->angle += 0.1;
	else if (key == LEFT)
		data->player->angle -= 0.1;

	if (data->player->angle < 0)
		data->player->angle += 2 * M_PI;
	else if (data->player->angle > 2 * M_PI)
		data->player->angle -= 2 * M_PI;
}


void	move_player(int key, t_data *data)
{
	if (key == RIGHT || key == LEFT)
		rotate_player(key, data);
	if (key == D_KEY || key == A_KEY)
		horizontal_moves(key, data);
	else if (key == S_KEY || key == W_KEY)
		vertical_moves(key, data);
}

void	draw_direction(t_data *data, int x, int y)
{
	double	current_x;
	double	current_y;
	int		i;
	int		len;

	i = 0;
	len = 100;
	while (i < len)
	{
		current_x = x + cos(data->player->angle) * i;
		current_y = y + sin(data->player->angle) * i;
		put_pixel_to_buffer(data->buffer, current_x, current_y, 0x29ab87);
		i++;
	}
}

void	draw_player(t_data *data, double x, double y)
{
	int		height;
	int		width;
	double	start_x;
	double	rotated_x;
	double	rotated_y;
	double	center_x;
	double	center_y;

	center_x = x + PLAYER_SIZE / 2;
	center_y = y + PLAYER_SIZE / 2;

	start_x = x;
	height = (int)y + PLAYER_SIZE;
	width = (int)x + PLAYER_SIZE;

	while (y < height)
	{
		x = start_x;
		while (x < width)
		{
			rotated_x = (x - center_x) * cos(data->player->angle) - (y - center_y) * sin(data->player->angle) + center_x;
			rotated_y = (x - center_x) * sin(data->player->angle) + (y - center_y)  * cos(data->player->angle) + center_y;
			
			put_pixel_to_buffer(data->buffer, rotated_x, rotated_y, 0xFF0000);
			x++;
		}
		y++;
	}
}
