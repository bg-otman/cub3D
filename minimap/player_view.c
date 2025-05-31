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

/*
// void	draw_direction(t_data *data, int x, int y, double angle)
// {
// 	double	current_x;
// 	double	current_y;
// 	int		i;
// 	int		len;

// 	len = WIN_WIDTH;
// 	i = 0;
// 	while (i < len)
// 	{
// 		current_x = x + cos(angle) * i;
// 		current_y = y + sin(angle) * i;
// 		if (is_wall(data->map, current_x, current_y))
// 			break ;
// 		put_pixel_to_buffer(data->buffer, current_x, current_y, 0x29ab87);
// 		i++;
// 	}
// }

// void	field_of_view(t_data *data, t_player *player)
// {
// 	int	i;

// 	i = 0;
// 	double j = 0;
// 	while (i < FOV)
// 	{
	// 		draw_direction(data, player->x + PLAYER_SIZE / 2,
// 			player->y + PLAYER_SIZE / 2, player->angle + j);
// 		i++;
// 		j += 0.01;
// 	}
// }
*/

void	init_cast(t_cast *cast, int x1, int y1)
{
	cast->x1 = x1;
	cast->y1 = y1;
	cast->dx = abs(x1 - cast->x0);
	cast->dy = abs(y1 - cast->y0);
	if (cast->x0 < x1)
		cast->sx = 1;
	else
		cast->sx = -1;
	if (cast->y0 < y1)
		cast->sy = 1;
	else
		cast->sy = -1;
	cast->err = cast->dx - cast->dy;
}

void	cast_ray(t_data *data, t_cast *cast, int x1, int y1)
{
	int	tmp;

	init_cast(cast, x1, y1);
	while (true)
	{
		put_pixel_to_buffer(data->buffer, cast->x0, cast->y0, RAY_COLOR);
		if (cast->x0 == x1 && cast->y0 == y1)
			break ;
		tmp = 2 * cast->err;
		if (tmp > -cast->dy)
		{
			cast->err -= cast->dy;
			cast->x0 += cast->sx;
		}
		if (tmp < cast->dx)
		{
			cast->err += cast->dx;
			cast->y0 += cast->sy;
		}
	}
}

void draw_direction(t_data *data, int x, int y, double angle)
{
	double	current_x;
	double	current_y;
	int		i;

	current_x = x;
	current_y = y;
	i = 0;
	while (i < MAX_RAY_LENGTH)
	{
		current_x = x + cos(angle) * i;
		current_y = y + sin(angle) * i;
		if (is_wall(data->map, current_x, current_y))
		{
			data->cast->x0 = x;
			data->cast->y0 = y;
			cast_ray(data, data->cast, (int)current_x, (int)current_y);
			break ;
		}
		i++;
	}
}

void field_of_view(t_data *data, t_player *player)
{
	double	angle_step;
	double	start_angle;
	double	ray_angle;
	int		i;

	data->cast = ft_malloc(sizeof(t_cast));
	angle_step = FOV / NUM_RAYS;
	start_angle = player->angle - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + (i * angle_step);
		draw_direction(data, player->x + PLAYER_SIZE / 2,
					   player->y + PLAYER_SIZE / 2, ray_angle);
		i++;
	}
}
