/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:43:49 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/22 17:02:37 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_rect(t_frame *frame, t_image *img)
{
	double	x;
	double	y;

	y = frame->y;
	while (y < frame->hieght)
	{
		x = frame->x;
		while (x < frame->width)
		{
			put_pixel_to_buffer(img, x, y, 0x2d3142);
			x++;
		}
		y++;
	}
}

/*
 * * * order of drawing * * *
 *	TOP
 *	BOTTOM
 *	LEFT
 *	RIGHT
*/
void	draw_frame(t_frame *frame, t_image *img, t_view view)
{
	int	minimap_width;
	int	minimap_height;

	minimap_width = (view.end_col - view.start_col + 1) * MM_TILE_SIZE;
	minimap_height = (view.end_row - view.start_row + 1) * MM_TILE_SIZE;
	frame->x = MM_OFFSET_X - 1;
	frame->y = MM_OFFSET_Y - MM_TILE_SIZE;
	frame->hieght = frame->y + MM_TILE_SIZE - 1;
	frame->width = MM_OFFSET_X + minimap_width;
	draw_rect(frame, img);
	frame->x = MM_OFFSET_X - MM_TILE_SIZE;
	frame->y = MM_OFFSET_Y + minimap_height - 1;
	frame->hieght = frame->y + MM_TILE_SIZE - 1;
	frame->width = MM_OFFSET_X + minimap_width + MM_TILE_SIZE - 1;
	draw_rect(frame, img);
	frame->x = MM_OFFSET_X - MM_TILE_SIZE;
	frame->y = MM_OFFSET_Y - MM_TILE_SIZE;
	frame->hieght = MM_OFFSET_Y + minimap_height;
	frame->width = frame->x + MM_TILE_SIZE;
	draw_rect(frame, img);
	frame->x = MM_OFFSET_X + minimap_width - 1;
	frame->y = MM_OFFSET_Y - MM_TILE_SIZE;
	frame->hieght = MM_OFFSET_Y + minimap_height;
	frame->width = frame->x + MM_TILE_SIZE;
	draw_rect(frame, img);
}

void	adjust_view_range(t_data *data, t_view *view)
{
	if (data->map_width > MM_VIEW_RANGE * 2)
	{
		if (view->start_col == 0)
			view->end_col = MM_VIEW_RANGE * 2;
		else if (view->end_col == data->map_width - 1)
			view->start_col = data->map_width - (MM_VIEW_RANGE * 2) - 1;
	}
	if (data->map_height > MM_VIEW_RANGE * 2)
	{
		if (view->start_row == 0)
			view->end_row = MM_VIEW_RANGE * 2;
		else if (view->end_row == data->map_height - 1)
			view->start_row = data->map_height - (MM_VIEW_RANGE * 2) - 1;
	}
}

void	get_map_view_range(t_data *data)
{
	t_view	*view;

	view = &data->view;
	view->start_row = data->player->y / TILE_SIZE - MM_VIEW_RANGE;
	if (view->start_row < 0)
		view->start_row = 0;
	view->start_col = data->player->x / TILE_SIZE - MM_VIEW_RANGE;
	if (view->start_col < 0)
		view->start_col = 0;
	view->end_row = data->player->y / TILE_SIZE + MM_VIEW_RANGE;
	if (view->end_row >= data->map_height)
		view->end_row = data->map_height - 1;
	view->end_col = data->player->x / TILE_SIZE + MM_VIEW_RANGE;
	if (view->end_col >= data->map_width)
		view->end_col = data->map_width - 1;
	adjust_view_range(data, view);
}
