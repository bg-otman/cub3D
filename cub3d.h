/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:13 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/22 20:09:08 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing/get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>

# define ESCAPE 65307
# define RIGHT 65363
# define LEFT 65361
# define DOWN 65364
# define UP 65362
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define W_KEY 119
# define WHITE_SPACES " \t\n\v\f\r"

typedef struct s_image
{
	void		*img_ptr;
	char		*pixel_data;
	int			bpp;
	int			endian;
	int			line_size;
	int			width;
	int			height;
}				t_image;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
} t_color;

typedef struct s_data
{
	char	**map;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	*img_wall;
	t_color	*floor;
	t_color	*ceiling;
	int		map_height;
	int		map_width;
	int		player_x;
	int		player_y;
	int		exit_status;
	char	player_dir;
} t_data;

// utils
void	put_error(char	*msg, t_data *data, bool sys_error);
void	clean_exit(t_data *data);
bool	ft_isspace(char c);
int		skip_spacess(const char *str);
// parsing
void	read_map(const char *map_path, int offset, t_data *data);
void	get_map_data(const char *map_path, t_data *data);
void	parse_map(t_data *data, char *av[]);
void	map_len(int fd, t_data *data);

#endif