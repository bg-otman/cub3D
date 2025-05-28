/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:52:22 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/28 06:17:11 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_block(t_data *data, int x, int y, int color)
{
	int	height;
	int	width;
	int	start_x;

	start_x = x;
	height = y + TILE_SIZE;
	width = x + TILE_SIZE;
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
	y = MINIMAP_OFFSET_Y;
	while (map[i])
	{
		j = 0;
		x = MINIMAP_OFFSET_X;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_block(data, x, y, 0x0047ab);
			else if (!ft_isspace(map[i][j]))
				draw_block(data, x, y, 0xFFFFFF);
			x += MINIMAP_OFFSET_X;
			j++;
		}
		y += MINIMAP_OFFSET_Y;
		i++;
	}
}
