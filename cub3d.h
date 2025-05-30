/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:13 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/30 10:20:23 by obouizi          ###   ########.fr       */
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
# include <math.h>

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
# define WIN_WIDTH 1500
# define WIN_HEIGHT 800
# define PLAYER_SIZE 20
# define TILE_SIZE 30
# define MINIMAP_OFFSET_X TILE_SIZE
# define MINIMAP_OFFSET_Y TILE_SIZE

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

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	radius;
    double	angle;
    double	rotation_speed;
    double	move_speed;
	char	direction;
} t_player;

typedef struct s_data
{
	char		**map;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		*img_wall;
	t_image		*buffer;
	t_color		*floor;
	t_color		*ceiling;
	t_player	*player;
	int			map_height;
	int			map_width;
	int			exit_status;
} t_data;

// main
void	draw(t_data *data);
// utils
void	put_error(char	*msg, t_data *data, bool sys_error);
void	init_buffer(t_data *data);
void	put_pixel_to_buffer(t_image *img, int x, int y, int color);
void	get_player_pos(char **map, double *x, double *y, char *player_dir);
void	clear_buffer_img(t_image *buffer, int color);
void	init_player(t_data *data);
bool	check_textures(char *line);
bool	is_line_empty(char *line);
bool	is_valid_char(char c);
bool	ft_isspace(char c);
bool	is_valid_key(int key);
int		skip_spacess(const char *str);
int		clean_exit(t_data *data);
// parsing
void	read_map(const char *map_path, int offset, t_data *data);
void	get_map_data(const char *map_path, t_data *data);
void	check_walls(char **map, t_data *data);
void	parse_map(t_data *data, char *av[]);
void	map_len(int fd, t_data *data);
// minimap
void draw_player(t_data *data, int center_x, int center_y, int radius);
// void	draw_player(t_data *data, double x, double y);
void	draw_minimap(char **map, t_data *data);
void	player_rotation(int key, t_data *data);
void	move_player(int key, t_data *data);
void	draw_direction(t_data *data);

#endif