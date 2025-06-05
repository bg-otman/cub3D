/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:49 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/04 23:18:28 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->buffer->img_ptr);
	data->buffer->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT);
	data->buffer->pixel_data = mlx_get_data_addr(
			data->buffer->img_ptr, &data->buffer->bpp,
			&data->buffer->line_size, &data->buffer->endian);
	if (key == ESCAPE)
		clean_exit(data);
	if (is_valid_key(key))
		move_player(key, data);
	draw(data);
	return (1);
}

void	draw(t_data *data)
{
	int (i);
	i = 0;
	clear_buffer_img(data->buffer, 0x000000);
	cieling_and_floor(data);
	while (i < NUM_RAYS)
	{
		ray_casting(data, ((data->player->angle - (FOV / 2)) + (i * (FOV / NUM_RAYS))), i);
		i++;
	}
	draw_minimap(data->map, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->buffer->img_ptr,
		0, 0);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac != 2)
		return (write(2, "Error\nInvalid args\n", 20), 1);
	ft_memset(&data, 0, sizeof(t_data));
	parse_map(&data, av + 1);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	init_buffer(&data);
	init_player(&data);
	draw(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, (t_data *)&data);
	mlx_hook(data.win_ptr, 17, 0, clean_exit, (t_data *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
