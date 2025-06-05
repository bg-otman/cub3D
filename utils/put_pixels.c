/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:16:44 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/05 14:59:50 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

unsigned int	get_pixel_color(t_image *img, int x, int y)
{
	return (*(unsigned int *)((img->pixel_data + (y * img->line_size) + (x
				* img->bpp / 8))));
}

void	put_img_to_buffer(t_image *buffer_img, t_image *img, int x, int y)
{
	int	i;
	int	j;

	if (!img || !buffer_img)
		return ;
	j = 0;
	while (j < img->height)
	{
		i = 0;
		while (i < img->width)
		{
			put_pixel_to_buffer(buffer_img, x + i, y + j, get_pixel_color(img,
					i, j));
			i++;
		}
		j++;
	}
}
