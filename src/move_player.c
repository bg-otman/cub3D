/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:10:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/23 13:12:57 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_wall(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = (x / TILE_SIZE);
	map_y = (y / TILE_SIZE);
	if (map_y < 0 || !data->map[map_y])
		return (true);
	if (map_x < 0 || map_x >= (int)ft_strlen(data->map[map_y]))
		return (true);
	if (data->map[map_y][map_x] == '1')
		return (true);
	if (data->map[map_y][map_x] == 'D' && is_door_close(data, map_y, map_x))
		return (true);
	return (false);
}

void	is_collision(t_data *data, double x, double y)
{
	if (!(is_wall(data, x, y)
			|| is_wall(data, x + PLAYER_SIZE, y)
			|| is_wall(data, x, y + PLAYER_SIZE)
			|| is_wall(data, x + PLAYER_SIZE, y + PLAYER_SIZE)))
	{
		data->player->x = x;
		data->player->y = y;
	}
}

void	update_position(t_data *d, int key)
{
	double (new_x), (new_y);
	new_x = d->player->x;
	new_y = d->player->y;
	if (key == S_KEY)
	{
		new_x -= d->player->dx;
		new_y -= d->player->dy;
	}
	else if (key == W_KEY)
	{
		new_x += d->player->dx;
		new_y += d->player->dy;
	}
	else if (key == D_KEY)
	{
		new_x += cos(d->player->angle + M_PI_2) * d->player->move_speed;
		new_y += sin(d->player->angle + M_PI_2) * d->player->move_speed;
	}
	else if (key == A_KEY)
	{
		new_x += cos(d->player->angle - M_PI_2) * d->player->move_speed;
		new_y += sin(d->player->angle - M_PI_2) * d->player->move_speed;
	}
	is_collision(d, new_x, d->player->y);
	is_collision(d, d->player->x, new_y);
}

void	move_player(int key, t_data *data)
{
	player_rotation(key, data);
	if (key == D_KEY || key == A_KEY || key == S_KEY || key == W_KEY)
		update_position(data, key);
}
