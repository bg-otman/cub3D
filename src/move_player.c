/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:10:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/04 23:25:25 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_wall(char **map, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = (x / TILE_SIZE);
	map_y = (y / TILE_SIZE);
	if (map_y < 0 || !map[map_y])
		return (true);
	if (map_x < 0 || map_x >= (int)ft_strlen(map[map_y]))
		return (true);
	if (map[map_y][map_x] == '1')
		return (true);
	return (false);
}

void	check_all_sides(t_player *player, char **map, double new_x,
		double new_y)
{
	(void) map;
	if (!is_wall(map, new_x, new_y) && !is_wall(map, new_x + PLAYER_SIZE - 1,
			new_y) && !is_wall(map, new_x, new_y + PLAYER_SIZE - 1)
		&& !is_wall(map, new_x + PLAYER_SIZE - 1, new_y + PLAYER_SIZE - 1))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	update_position(t_player *player, char **map, int key)
{
	double (new_x), (new_y);
	new_x = player->x;
	new_y = player->y;
	if (key == S_KEY)
	{
		new_x = player->x - player->dx;
		new_y = player->y - player->dy;
	}
	else if (key == W_KEY)
	{
		new_x = player->x + player->dx;
		new_y = player->y + player->dy;
	}
	else if (key == D_KEY)
	{
		new_x = player->x + cos(player->angle + M_PI_2) * player->move_speed;
		new_y = player->y + sin(player->angle + M_PI_2) * player->move_speed;
	}
	else if (key == A_KEY)
	{
		new_x = player->x + cos(player->angle - M_PI_2) * player->move_speed;
		new_y = player->y + sin(player->angle - M_PI_2) * player->move_speed;
	}
	check_all_sides(player, map, new_x, new_y);
}

void	move_player(int key, t_data *data)
{
	player_rotation(key, data);
	if (key == D_KEY || key == A_KEY || key == S_KEY || key == W_KEY)
		update_position(data->player, data->map, key);
}

void	draw_player(t_data *data, int center_x, int center_y, int radius)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

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
