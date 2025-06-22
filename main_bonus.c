/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:49 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/22 18:11:45 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'D');
}

int	key_press(int key, t_data *data)
{
	if (key == ESCAPE)
		clean_exit(data);
	if (is_valid_key(key))
		move_player(key, data);
	if (key == SPACE)
		open_door(data, data->player->x, data->player->y);
	return (1);
}

void	draw(t_data *data)
{
	clear_buffer_img(data->buffer, 0x000000);
	field_of_view(data);
	draw_minimap(data->map, data);
	shoot(data->buffer, data->player_img, data->shoot_frame);
	hand_animation(data->buffer, data->hand_sprites, data->hand_frame);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->buffer->img_ptr,
		0, 0);
}

int	update_frame(t_data *data)
{
	if (data->is_shooting)
	{
		if (data->shoot_frame < GUN_NUM_SPRITES * 10)
			data->shoot_frame++;
		else
		{
			data->is_shooting = false;
			data->shoot_frame = 0;
		}
	}
	if (data->hand_frame < HAND_SPRITES * 15)
		data->hand_frame++;
	else
		data->hand_frame = 0;
	update_doors(data, data->doors);
	draw(data);
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac != 2)
		return (write(2, "Error\nInvalid args\n", 20), 1);
	ft_memset(&data, 0, sizeof(t_data));
	parse_map(&data, av + 1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		put_error("Error\nFailed to initialise mlx : ", &data, true);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data.mlx_ptr)
		put_error("Error\nFailed to open window : ", &data, true);
	init_buffer(&data);
	init_player(&data);
	init_doors(&data);
	load_textures(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, (t_data *)&data);
	mlx_hook(data.win_ptr, 17, 0, clean_exit, (t_data *)&data);
	mlx_hook(data.win_ptr, 6, 1L << 6, mouse_rotate, (t_data *)&data);
	mlx_mouse_hook(data.win_ptr, mouse_click, (t_data *)&data);
	mlx_loop_hook(data.mlx_ptr, update_frame, (t_data *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
