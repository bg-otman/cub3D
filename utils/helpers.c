/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:24:23 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/22 15:18:00 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	shoot(t_image *buffer, t_image **player_img, int shoot_frame)
{
	int	sprite_index;

	sprite_index = (shoot_frame / 10) % GUN_NUM_SPRITES;
	put_img_to_buffer(buffer, player_img[sprite_index], WIN_WIDTH / 1.8,
		WIN_HEIGHT - player_img[sprite_index]->height);
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	skip_spacess(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

bool	is_line_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

bool	is_valid_key(int key)
{
	if (key == LEFT || key == RIGHT || key == UP || key == DOWN
		|| key == D_KEY || key == S_KEY || key == A_KEY || key == W_KEY)
		return (true);
	return (false);
}
