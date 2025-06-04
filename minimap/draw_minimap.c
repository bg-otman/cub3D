/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:52:22 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/03 13:58:03 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_block(t_data *data, int x, int y, int color)
{
	int	height;
	int	width;
	int	start_x;

	start_x = x;
	height = MM_OFFSET_Y + y + TILE_SIZE * MINIMAP_SCALE;
	width = MM_OFFSET_X + x + TILE_SIZE * MINIMAP_SCALE;
	while (y < height)
	{
		x = start_x;
		while (x < width)
		{
			put_pixel_to_buffer(data->buffer, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_direction(t_data *data, int x, int y, double angle)
{
	double	current_x;
	double	current_y;
	int		i;

	current_x = x;
	current_y = y;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		current_x = x + cos(angle) * i;
		current_y = y + sin(angle) * i;
		put_pixel_to_buffer(data->buffer, current_x, current_y, 0x0047ab);
		i++;
	}
}

void	draw_player_minimap(t_data *data, int center_x, int center_y,
		int radius)
{
	int (x), (y), (dx), (dy);
	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			dx = x - center_x;
			dy = y - center_y;
			if (pow(dx, 2) + pow(dy, 2) <= pow(radius, 2))
				put_pixel_to_buffer(data->buffer, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	draw_minimap(char **map, t_data *data)
{
	int (i), (j), (x), (y);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			x = MM_OFFSET_X + j * MM_TILE_SIZE;
			y = MM_OFFSET_Y + i * MM_TILE_SIZE;
			if (map[i][j] == '1')
				draw_block(data, x, y, 0x0047ab);
			else if (!ft_isspace(map[i][j]))
				draw_block(data, x, y, 0xFFFFFF);
			j++;
		}
		i++;
	}
	draw_player_minimap(data, MM_OFFSET_X + (data->player->x * MINIMAP_SCALE)
		- (PLAYER_SIZE * MINIMAP_SCALE) / 2, MM_OFFSET_Y + (data->player->y
			* MINIMAP_SCALE) - (PLAYER_SIZE * MINIMAP_SCALE) / 2,
		(PLAYER_SIZE * MINIMAP_SCALE));
	draw_direction(data, MM_OFFSET_X + (data->player->x * MINIMAP_SCALE)
		- (PLAYER_SIZE * MINIMAP_SCALE) / 2, MM_OFFSET_Y + (data->player->y
			* MINIMAP_SCALE) - (PLAYER_SIZE * MINIMAP_SCALE) / 2, data->player->angle);
}
