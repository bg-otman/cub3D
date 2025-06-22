/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:59:44 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/22 17:59:45 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_sprites(t_data *data, t_image **sprites, int sprites_num)
{
	int	i;

	i = 0;
	if (!sprites)
		return ;
	while (i < sprites_num)
	{
		if (sprites[i])
			mlx_destroy_image(data->mlx_ptr, sprites[i]->img_ptr);
		i++;
	}
}

int	clean_exit(t_data *data)
{
	if (!data)
		(free_garbage(), exit(EXIT_FAILURE));
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->buffer && data->buffer->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->buffer->img_ptr);
	if (data->door_img && data->door_img->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->door_img->img_ptr);
	if (data->no && data->no->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->no->img_ptr);
	if (data->so && data->so->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->so->img_ptr);
	if (data->ea && data->ea->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->ea->img_ptr);
	if (data->we && data->we->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->we->img_ptr);
	free_sprites(data, data->player_img, GUN_NUM_SPRITES);
	free_sprites(data, data->hand_sprites, HAND_SPRITES);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_garbage();
	exit(data->exit_status);
}

unsigned int	get_pixel_color(t_image *img, int x, int y)
{
	return (*(unsigned int *)((img->pixel_data + (y * img->line_size) + (x
				* img->bpp / 8))));
}

void	hand_animation(t_image *buffer, t_image **hand_sprites, int hand_frame)
{
	int	sprite_index;

	sprite_index = (hand_frame / 15) % HAND_SPRITES;
	put_img_to_buffer(buffer, hand_sprites[sprite_index], WIN_WIDTH / 4.8,
		WIN_HEIGHT - hand_sprites[sprite_index]->height);
}

int	mouse_click(int button, int x, int y, t_data *data)
{
	(void) x;
	(void) y;
	if (button == 1 && !data->is_shooting)
		data->is_shooting = true;
	return (0);
}
