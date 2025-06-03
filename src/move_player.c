/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:10:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/03 21:29:39 by obouizi          ###   ########.fr       */
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

void	is_collision(t_player *player, char **map, double x, double y)
{
	if (!(is_wall(map, x, y)
			|| is_wall(map, x + PLAYER_SIZE - 1, y)
			|| is_wall(map, x, y + PLAYER_SIZE - 1)
			|| is_wall(map, x + PLAYER_SIZE - 1, y + PLAYER_SIZE - 1)))
	{
		player->x = x;
		player->y = y;
	}
}

void	update_position(t_player *player, char **map, int key)
{
	double (new_x), (new_y);
	new_x = player->x;
	new_y = player->y;
	if (key == S_KEY)
	{
		new_x -= player->dx;
		new_y -= player->dy;
	}
	else if (key == W_KEY)
	{
		new_x += player->dx;
		new_y += player->dy;
	}
	else if (key == D_KEY)
	{
		new_x += cos(player->angle + M_PI_2) * player->move_speed;
		new_y += sin(player->angle + M_PI_2) * player->move_speed;
	}
	else if (key == A_KEY)
	{
		new_x += cos(player->angle - M_PI_2) * player->move_speed;
		new_y += sin(player->angle - M_PI_2) * player->move_speed;
	}
	is_collision(player, map, new_x, new_y);
}

void	move_player(int key, t_data *data)
{
	player_rotation(key, data);
	if (key == D_KEY || key == A_KEY || key == S_KEY || key == W_KEY)
		update_position(data->player, data->map, key);
}
