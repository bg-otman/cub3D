/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:49 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/10 15:07:41 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == ESCAPE)
		clean_exit(data);
	if (is_valid_key(key))
		move_player(key, data);
	if (key == ENTER && !data->is_shooting)
		data->is_shooting = true;
	return (1);
}

void	shoot(t_image *buffer, t_image **player_img, int shoot_frame)
{
	int	sprite_index;

	sprite_index = (shoot_frame / 10) % GUN_NUM_SPRITES;
	put_img_to_buffer(buffer, player_img[sprite_index],
		WIN_WIDTH / 1.8, WIN_HEIGHT - player_img[sprite_index]->height - 1);
}

void	draw(t_data *data)
{
	clear_buffer_img(data->buffer, 0x000000);
	ceiling_and_floor(data);
	field_of_view(data);
	draw_minimap(data->map, data);
	shoot(data->buffer, data->player_img, data->shoot_frame);
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
	load_textures(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, (t_data *)&data);
	mlx_hook(data.win_ptr, 17, 0, clean_exit, (t_data *)&data);
	mlx_hook(data.win_ptr, 6, 1L << 6, mouse_rotate, (t_data *) &data);
	mlx_loop_hook(data.mlx_ptr, update_frame, (t_data *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
