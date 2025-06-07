/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:43:09 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/03 21:24:56 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_rotation(int key, t_data *data)
{
	t_player	*player;

	player = data->player;
	if (key == RIGHT)
		player->angle += player->rotation_speed;
	else if (key == LEFT)
		player->angle -= player->rotation_speed;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	else if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
	player->dx = cos(player->angle) * player->move_speed;
	player->dy = sin(player->angle) * player->move_speed;
}

int	mouse_rotate(int x, int y, t_data *data)
{
	static int old_x = -1;
	int delta;
	(void) y;

	if (old_x == -1)
		old_x = x;
	delta = x - old_x;
	if (delta == 0)
		return (0);
	data->player->angle += delta * (data->player->rotation_speed / 15);
	old_x = x;
	return (1);
}

void	ceiling_and_floor(t_data *data)
{
	unsigned int	ceiling_clr;
	unsigned int	floor_clr;

	int(x), (y);
	ceiling_clr = get_rgb_color(data->ceiling->r, data->ceiling->g,
			data->ceiling->b);
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
			put_pixel_to_buffer(data->buffer, x++, y, ceiling_clr);
		y++;
	}
	floor_clr = get_rgb_color(data->floor->r, data->floor->g, data->floor->b);
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
			put_pixel_to_buffer(data->buffer, x++, y, floor_clr);
		y++;
	}
}
