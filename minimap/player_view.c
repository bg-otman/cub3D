/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:43:09 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/30 15:09:52 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_rotation(int key, t_data *data)
{
	t_player	*player;

	player = data->player;
	if (key == RIGHT)
		player->angle += 0.1;
	else if (key == LEFT)
		player->angle -= 0.1;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	else if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
	player->dx = cos(player->angle) * player->move_speed;
	player->dy = sin(player->angle) * player->move_speed;
}

void	draw_direction(t_data *data, int len)
{
	double	current_x;
	double	current_y;
	int		x;
	int		y;
	int		i;

	x = data->player->x + PLAYER_SIZE / 2;
	y = data->player->y + PLAYER_SIZE / 2;
	i = 0;
	while (i < len)
	{
		current_x = x + cos(data->player->angle) * i;
		current_y = y + sin(data->player->angle) * i;
		put_pixel_to_buffer(data->buffer, current_x, current_y, 0x29ab87);
		i++;
	}
}
