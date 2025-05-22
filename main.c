/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:49 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/22 19:45:53 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char *av[])
{
    t_data  data;
	
    if (ac != 2)
		return (write(2, "Error\nInvalid args\n", 20), 1);
	ft_memset(&data, 0, sizeof(t_data));
	parse_map(&data, av + 1);
	free_garbage();// temporary until we init mlx
    return (0);
}
