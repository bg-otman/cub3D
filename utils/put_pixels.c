/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:16:44 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/23 14:19:17 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_image	*get_tex_img(t_data *data, t_texture tex)
{
	t_door	*door;

	door = get_door_at(data, tex.ray->map_x, tex.ray->map_y);
	if (door || is_door(data, tex.ray->map_x + 1, tex.ray->map_y)
		|| is_door(data, tex.ray->map_x, tex.ray->map_y + 1))
		return (data->door_img);
	if (tex.ray->side == 0)
	{
		if (tex.ray->ray_dir_x > 0)
			return (data->ea);
		else
			return (data->we);
	}
	else
	{
		if (tex.ray->ray_dir_y > 0)
			return (data->so);
		else
			return (data->no);
	}
}

void	clear_buffer_img(t_image *buffer, int color)
{
	int (x), (y);
	y = 0;
	while (y < buffer->height)
	{
		x = 0;
		while (x < buffer->width)
		{
			put_pixel_to_buffer(buffer, x, y, color);
			x++;
		}
		y++;
	}
}

bool	is_green_screen_color(int color)
{
	int (r), (g), (b);
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	return (r < 100 && g > 100 && b < 100);
}

void	put_pixel_to_buffer(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		dst = img->pixel_data + (y * img->line_size + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_img_to_buffer(t_image *buffer_img, t_image *img, int x, int y)
{
	int	i;
	int	j;
	int	color;

	if (!img || !buffer_img)
		return ;
	j = 0;
	while (j < img->height)
	{
		i = 0;
		while (i < img->width)
		{
			color = get_pixel_color(img, i, j);
			if (!img->has_green_screen || (img->has_green_screen
					&& !is_green_screen_color(color)))
				put_pixel_to_buffer(buffer_img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}
