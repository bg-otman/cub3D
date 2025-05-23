/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:08:24 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/24 00:19:22 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_error(char	*msg, t_data *data, bool sys_error)
{
	ft_putstr_fd(msg, 2);
	if (sys_error)
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	data->exit_status = EXIT_FAILURE;
	clean_exit(data);
}

void	clean_exit(t_data *data)
{
	if (data)
		return (free_garbage(), exit(EXIT_FAILURE));
	
	free_garbage();
	exit(data->exit_status);
}

bool	check_textures(char *line)
{
	int	i;
	if (!line)
		return (false);
	i = skip_spacess(line);
	if (!line[i])
		return (true);
	if (!ft_strncmp("F", line, 1) || !ft_strncmp("C", line, 1))
	{
		i++;
		if (!ft_isspace(line[i]))
			return (false);
		return (true);
	}
	if (ft_strncmp("NO", line, 2) && ft_strncmp("SO", line, 2)
		&& ft_strncmp("WE", line, 2) && ft_strncmp("EA", line, 2))
		return (false);
	i += 2;
	if (!ft_isspace(line[i]))
		return (false);
	return (true);
}
