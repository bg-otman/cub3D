/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:49 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/22 17:01:05 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	key_press(int key, t_data *data)
{
	if (key == ESCAPE)
		clean_exit(data);
	if (is_valid_key(key))
		move_player(key, data);
	return (1);
}

int	draw(t_data *data)
{
	clear_buffer_img(data->buffer, 0x000000);
	field_of_view(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->buffer->img_ptr,
		0, 0);
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
	mlx_loop_hook(data.mlx_ptr, draw, (t_data *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
