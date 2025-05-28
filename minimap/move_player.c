/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:10:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/28 06:34:34 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_wall(char **map, int	x, int	y)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (map_y < 0 || !map[map_y])
		return (true);

	if (map_x < 0 || map_x >= (int) ft_strlen(map[map_y]))
		return (true);

	if (map[map_y][map_x] == '1')
		return (true);

	return (false);
}

int	get_remaining_dist(t_data *data, int speed, int key)
{
	bool	res;
	
	res = true;
	while (--speed > 0)
	{
		if (key == D_KEY)
			res = is_wall(data->map, data->player->x + speed, data->player->y);
		else if (key == A_KEY)
			res = is_wall(data->map, data->player->x - speed, data->player->y);
		else if (key == W_KEY)
			res = is_wall(data->map, data->player->x, data->player->y - speed);
		else if (S_KEY)
			res = is_wall(data->map, data->player->x, data->player->y + speed);
		if (!res)
			return (speed);
	}
	return (0);
}

void	horizontal_moves(int key, t_data *data)
{
	int	speed;

	speed = data->player->move_speed;
	if (key == D_KEY)
	{
		if (is_wall(data->map, data->player->x + speed, data->player->y))
			speed = get_remaining_dist(data, speed, key);
		data->player->x += speed;
	}
	else if (key == A_KEY)
	{
		if (is_wall(data->map, data->player->x - speed - PLAYER_SIZE, data->player->y))
			speed = get_remaining_dist(data, speed - PLAYER_SIZE, key);
		data->player->x -= speed;
	}
}

void	vertical_moves(int key, t_data *data)
{
	int	speed;

	speed = data->player->move_speed;
	if (key == S_KEY)
	{
		if (is_wall(data->map, data->player->x, data->player->y + speed))
			speed = get_remaining_dist(data, speed, key);
		data->player->y += speed;
	}
	else if (key == W_KEY)
	{
		if (is_wall(data->map, data->player->x, data->player->y - speed - PLAYER_SIZE + 1))
			speed = get_remaining_dist(data, speed - PLAYER_SIZE + 1, key);
		data->player->y -= speed;
	}
}

void	move_player(int key, t_data *data)
{
	if (key == D_KEY || key == A_KEY)
		horizontal_moves(key, data);
	else if (key == S_KEY || key == W_KEY)
		vertical_moves(key, data);
}

void	draw_player(t_data *data, int x, int y)
{
	int	height;
	int	width;
	int	start_x;

	start_x = x;
	height = y + PLAYER_SIZE;
	width = x + PLAYER_SIZE;
	while (y < height)
	{
		x = start_x;
		while (x < width)
		{
			put_pixel_to_buffer(data->buffer, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}
