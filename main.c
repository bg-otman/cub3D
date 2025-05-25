/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:49 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/25 16:55:07 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_pos(char **map, t_data *data)
{
	int i;
	int j;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N')
			{
				data->player_x = i;
				data->player_y = j;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	key_press(int key, t_data *data)
{
	if (key == ESCAPE)
		clean_exit(data);
	if (is_valid_key(key))
		move_player(key, data);
	draw(data);
	return (1);
}

void	draw(t_data *data)
{
	clear_buffer_img(data->buffer, 0x000000);
	// get_player_pos(data->map, data);
	draw_minimap(data->map, data);
	draw_player(data, PLAYER_SIZE, data->player_x, data->player_y);
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
	draw(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, (t_data *)&data);
	mlx_hook(data.win_ptr, 17, 0, clean_exit, (t_data *)&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
