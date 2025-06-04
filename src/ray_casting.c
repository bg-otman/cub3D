/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:28:17 by asajed            #+#    #+#             */
/*   Updated: 2025/06/04 23:20:22 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_strip(t_data *data, double len, int x)
{
	double	strip;
	int		first;
	int		last;
	int		i;

	i = 0;
	strip = (TILE_SIZE / len) * ((WIN_WIDTH / 2) / tan(FOV / 2));
	first = (WIN_HEIGHT / 2) - (strip / 2);
	if (first < 0)
		first = 0;
	last = (WIN_HEIGHT / 2) + (strip / 2);
	if (last > WIN_HEIGHT)
		last = WIN_HEIGHT;
	while (first++ < last)
		put_pixel_to_buffer(data->buffer, x, first, 0xFF0000);
}

int	my_bool(bool condition, int yes, int no)
{
	if (condition)
		return (yes);
	return (no);
}

void ray_casting(t_data *data, double angle, int column_x)
{
	double	step_x;
	double	step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		side;
	int		wall_dist;

	map_x = (int)floor(data->player->x);
	map_y = (int)floor(data->player->y);
	step_x = my_bool((cos(angle) < 0), -1, 1);
	step_y = my_bool((sin(angle) < 0), -1, 1);
	side_dist_x = (data->player->x - map_x) * fabs(1.0 / cos(angle));
	if (step_x > 0)
		side_dist_x = ((map_x + 1.0) - data->player->x) * fabs(1.0 / cos(angle));
	side_dist_y = (data->player->y - map_y) * fabs(1.0 / sin(angle));
	if (step_y > 0)
		side_dist_y = ((map_y + 1.0) - data->player->y) * fabs(1.0 / sin(angle));
	side = 0;
	while (!is_wall(data->map, map_x, map_y))
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += fabs(1.0 / cos(angle));
			map_x += (int)step_x;
			side = 0;
		}
		else
		{
			side_dist_y += fabs(1.0 / sin(angle));
			map_y += (int)step_y;
			side = 1;
		}
	}
	if (side == 0)
		wall_dist = (int)((map_x - data->player->x + (1 - step_x) / 2) / cos(angle));
	else
		wall_dist = (int)((map_y - data->player->y + (1 - step_y) / 2) / sin(angle));
	draw_strip(data, wall_dist, column_x);
}
