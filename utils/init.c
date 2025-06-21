/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:11:43 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/21 18:32:31 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_buffer(t_data *data)
{
	data->buffer = ft_malloc(sizeof(t_image));
	if (!data->buffer)
		put_error("Error\nAllocation failed for buffer",
			data, true);
	data->buffer->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT);
	if (!data->buffer->img_ptr)
		put_error("Error\nFailed to create buffer image!",
			data, true);
	data->buffer->pixel_data = mlx_get_data_addr(
			data->buffer->img_ptr, &data->buffer->bpp,
			&data->buffer->line_size, &data->buffer->endian);
	data->buffer->width = WIN_WIDTH;
	data->buffer->height = WIN_HEIGHT;
}

void	init_player(t_data *data)
{
	t_player	*player;

	player = ft_malloc(sizeof(t_player));
	data->player = player;
	ft_bzero(player, sizeof(t_player));
	player->move_speed = 3;
	player->rotation_speed = 0.09;
	player->dx = cos(player->angle) * player->move_speed;
	player->dy = sin(player->angle) * player->move_speed;
	get_player_pos(data->map, &player->x, &player->y, &player->direction);
	if (player->direction == 'N')
		player->angle = -M_PI / 2;
	else if (player->direction == 'S')
		player->angle = M_PI / 2;
	else if (player->direction == 'W')
		player->angle = M_PI;
	else
		player->angle = 0;
}

bool	init_texture(t_data *data, t_image **img, char *file_path)
{
	*img = ft_malloc(sizeof(t_image));
	(*img)->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, file_path,
			&((*img)->width), &((*img)->height));
	if (!(*img)->img_ptr)
	{
		put_error("Error\nFailed to load texture : ", data, true);
		data->exit_status = EXIT_FAILURE;
		return (false);
	}
	(*img)->pixel_data = mlx_get_data_addr((*img)->img_ptr, &(*img)->bpp,
			&(*img)->line_size, &(*img)->endian);
	return (true);
}

void	load_sprites(t_data *mlx, t_image **sprites, char *path, int sprite_num)
{
	int		i;
	char	full_path[50];
	char	*num;

	i = 0;
	while (i < sprite_num)
	{
		num = ft_itoa(i);
		ft_strlcpy(full_path, path, sizeof(full_path));
		ft_strlcat(full_path, num, sizeof(full_path));
		ft_strlcat(full_path, ".xpm", sizeof(full_path));
		init_texture(mlx, &(sprites[i]), full_path);
		if (HAND_SPRITES == sprite_num)
			sprites[i]->has_green_screen = true;
		else
			sprites[i]->has_green_screen = false;
		i++;
	}
}

void	load_textures(t_data *data)
{
	data->player_img = ft_malloc(sizeof(t_image *) * GUN_NUM_SPRITES + 1);
	data->player_img[GUN_NUM_SPRITES - 1] = NULL;
	load_sprites(data, data->player_img, "textures/gun", GUN_NUM_SPRITES);

	data->hand_sprites = ft_malloc(sizeof(t_image *) * HAND_SPRITES + 1);
	data->hand_sprites[HAND_SPRITES - 1] = NULL;
	load_sprites(data, data->hand_sprites, "textures/hand_sprites/", HAND_SPRITES);
	
	init_texture(data, &data->door_img, "textures/door.xpm");
	init_texture(data, &data->ea, data->ea_path);
	init_texture(data, &data->so, data->so_path);
	init_texture(data, &data->we, data->we_path);
	init_texture(data, &data->no, data->no_path);
}
