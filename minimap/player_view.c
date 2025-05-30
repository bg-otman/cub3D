/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:43:09 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/30 06:51:09 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_rotation(int key, t_data *data)
{
	t_player *player;

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

void	draw_line(t_data *data, int x, int y)
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

void	draw_direction(t_data *data)
{
	// if (!data->checked_dir)
	// {
	// 	if (data->player_dir == 'N')
	// 		data->player->angle = -M_PI / 2;
	// 	else if (data->player_dir == 'S')
	// 		data->player->angle = M_PI / 2;
	// 	else if (data->player_dir == 'W')
	// 		data->player->angle = M_PI;
	// 	else
	// 		data->player->angle = 0;
	// 	data->checked_dir = true;
	// }
	draw_line(data, data->player->x + PLAYER_SIZE / 2,
		data->player->y + PLAYER_SIZE / 2);
}
