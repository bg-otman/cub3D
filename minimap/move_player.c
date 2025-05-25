/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:10:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/25 16:42:04 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	horizontal_moves(int key, t_data *data)
{
	int	speed;
	int	remain_dist;

	speed = MOVE_SPEED;
	if (key == RIGHT || key == D_KEY)
	{
		remain_dist = WIN_WIDTH - (data->player_x + PLAYER_SIZE);
		if (remain_dist <= 0)
			speed = 0;
		else if (remain_dist < speed)
			speed = remain_dist;
		data->player_x += speed;
	}
	else if (key == LEFT || key == A_KEY)
	{
		remain_dist = data->player_x;
		if (remain_dist <= 0)
			speed = 0;
		else if (remain_dist < speed)
			speed = remain_dist;
		data->player_x -= speed;
	}
}

void	vertical_moves(int key, t_data *data)
{
	int	speed;
	int	remain_dist;

	speed = MOVE_SPEED;
	if (key == DOWN || key == S_KEY)
	{
		remain_dist = WIN_HEIGHT - (data->player_y + PLAYER_SIZE);
		if (remain_dist <= 0)
			speed = 0;
		else if (remain_dist < speed)
			speed = remain_dist;
		data->player_y += speed;
	}
	else if (key == UP || key == W_KEY)
	{
		remain_dist = data->player_y;
		if (remain_dist <= 0)
			speed = 0;
		else if (remain_dist < speed)
			speed = remain_dist;
		data->player_y -= speed;
	}
}

void	move_player(int key, t_data *data)
{
	if (key == RIGHT || key == D_KEY || key == LEFT || key == A_KEY)
		horizontal_moves(key, data);
	else if (key == DOWN || key == S_KEY || key == UP || key == W_KEY)
		vertical_moves(key, data);
}

void	draw_player(t_data *data, int square_size, int x, int y)
{
	int	height;
	int	width;
	int	start_x;

	start_x = x;
	height = y + square_size;
	width = x + square_size;
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
