/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:08:24 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/21 16:16:28 by obouizi          ###   ########.fr       */
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
