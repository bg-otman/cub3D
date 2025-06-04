/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:13 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/04 20:45:30 by obouizi          ###   ########.fr       */
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
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# ifndef M_PI_2
#  define M_PI_2 M_PI / 2
# endif

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
# define WIN_WIDTH 1000
# define WIN_HEIGHT 500
# define TILE_SIZE 30
# define PLAYER_SIZE TILE_SIZE / 2
# define MINIMAP_SCALE 0.4
# define MM_TILE_SIZE (TILE_SIZE * MINIMAP_SCALE)
# define MM_OFFSET_X 20
# define MM_OFFSET_Y 20
# define RAY_COLOR 0x29ab87
# define MAX_RAY_LENGTH WIN_WIDTH
# define NUM_RAYS 1500
# define FOV (M_PI / 4)
# define MM_VIEW_RANGE 5


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

typedef struct s_cast
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		tmp;
	int		err;
} t_cast;

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

typedef struct s_view
{
	int	start_row;
	int	end_row;
	int	start_col;
	int	end_col;
} t_view;


typedef struct s_frame
{
	double	x;
	double	y;
	double	width;
	double	hieght;
} t_frame;

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
	t_cast		*cast;
	t_player	*player;
	t_view		view;
	t_frame		frame;
	int			map_height;
	int			map_width;
	int			exit_status;
} t_data;

// src
void	draw(t_data *data);
void	move_player(int key, t_data *data);
bool	is_wall(char **map, int x, int y);
void	player_rotation(int key, t_data *data);
void	field_of_view(t_data *data, t_player *player);
void	ceiling_and_floor(t_data *data);
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
unsigned int	get_rgb_color(int red, int green, int blue);
// parsing
void	read_map(const char *map_path, int offset, t_data *data);
void	get_map_data(const char *map_path, t_data *data);
void	check_walls(char **map, t_data *data);
void	parse_map(t_data *data, char *av[]);
void	map_len(int fd, t_data *data);
// minimap
void	draw_minimap(char **map, t_data *data);
void	draw_frame(t_frame *frame, t_image *img, t_view  view);
void	get_map_view_range(t_data *data);

#endif
