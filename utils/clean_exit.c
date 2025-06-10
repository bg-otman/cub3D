/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:59:44 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/10 15:04:21 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_sprites(t_data *data, t_image **sprites, int sprites_num)
{
	int	i;

	i = 0;
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
	//// here free ressources loaded by mlx's funs
	if (data->buffer && data->buffer->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->buffer->img_ptr);
	free_sprites(data, data->player_img, GUN_NUM_SPRITES);
	/////
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_garbage();
	exit(data->exit_status);
}
