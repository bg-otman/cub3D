/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:52:22 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/04 20:45:41 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_block(t_data *data, int x, int y, int color)
{
	int	height;
	int	width;
	int	start_x;

	start_x = x;
	height = y + MM_TILE_SIZE;
	width = x + MM_TILE_SIZE;
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

void	draw_player(t_data *data, double center_x, double center_y,
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

void display_player(t_data *data)
{
    double x;
    double y;

    x = MM_OFFSET_X + ((data->player->x / TILE_SIZE) - data->view.start_col) * MM_TILE_SIZE
        - ((PLAYER_SIZE * MINIMAP_SCALE) / 2) + MM_TILE_SIZE / 2;
    y = MM_OFFSET_Y + ((data->player->y / TILE_SIZE) - data->view.start_row) * MM_TILE_SIZE
        - ((PLAYER_SIZE * MINIMAP_SCALE) / 2) + MM_TILE_SIZE / 2;
    draw_player(data, x, y, (PLAYER_SIZE * MINIMAP_SCALE));
    draw_direction(data, x, y, data->player->angle);
}

void	draw_minimap(char **map, t_data *data)
{
    int i, j, x, y;
    get_map_view_range(data);
	draw_frame(&data->frame, data->buffer, data->view);
    i = data->view.start_row;
	while (i <= data->view.end_row)
    {
        j = data->view.start_col;
        while (j <= data->view.end_col)
        {
            x = MM_OFFSET_X + (j - data->view.start_col) * MM_TILE_SIZE;
            y = MM_OFFSET_Y + (i - data->view.start_row) * MM_TILE_SIZE;
			draw_block(data, x - 1, y - 1, 0x000000);
            if (map[i][j] == '1')
                draw_block(data, x, y, 0x0047ab);
            else if (!ft_isspace(map[i][j]))
                draw_block(data, x, y, 0xFFFFFF);
            j++;
        }
        i++;
    }
    display_player(data);
}
