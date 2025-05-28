/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:11:43 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/27 16:39:43 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_buffer(t_data *data)
{
	data->buffer = malloc(sizeof(t_image));
	if (!data->buffer)
		put_error("Error\nAllocation failed for buffer",
			data, true);
	data->buffer->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT);
	if (!data->buffer->img_ptr)
		put_error("Error\nFailed to create buffer image!",
			data, true);
	data->buffer->pixel_data = mlx_get_data_addr(
			data->buffer->img_ptr, &data->buffer->bpp,
			&data->buffer->line_size, &data->buffer->endian);
	data->buffer->width = WIN_WIDTH;
	data->buffer->height = WIN_HEIGHT;
}

void	init_player(t_data *data)
{
	data->player = ft_malloc(sizeof(t_player));
	ft_bzero(data->player, sizeof(t_player));
	data->player->move_speed = 5;
	get_player_pos(data->map, &data->player->x, &data->player->y);
}
