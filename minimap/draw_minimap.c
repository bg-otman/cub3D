/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:52:22 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/25 16:52:58 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_block(t_data *data, int x, int y, int color)
{
	int	height;
	int	width;
	int	start_x;

	start_x = x;
	height = y + BLOCK_SIZE;
	width = x + BLOCK_SIZE;
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

void	draw_minimap(char **map, t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = BLOCK_SIZE;
	while (map[i])
	{
		j = 0;
		x = BLOCK_SIZE;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_block(data, x, y, 0x0000FF);
			else if (map[i][j] == '0')
				draw_block(data, x, y, 0xFFFFFF);
			else if (map[i][j] == 'N')
				draw_player(data, PLAYER_SIZE, data->player_x, data->player_y);
			// draw_block(data, x, y, 0xFF0000);
			j++;
			x += BLOCK_SIZE;
		}
		y += BLOCK_SIZE;
		i++;
	}
}
