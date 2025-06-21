/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:13 by obouizi           #+#    #+#             */
/*   Updated: 2025/06/21 20:59:59 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "parsing/get_next_line/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define ESCAPE 65307
# define RIGHT 65363
# define LEFT 65361
# define DOWN 65364
# define UP 65362
# define ENTER 65293
# define SPACE 32
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define W_KEY 119
# define WHITE_SPACES " \t\n\v\f\r"
# define WIN_WIDTH 1000
# define WIN_HEIGHT 500
# define TILE_SIZE 30
# define PLAYER_SIZE 15 // TILE_SIZE / 2
# define MINIMAP_SCALE 0.4
# define MM_TILE_SIZE 12 // TILE_SIZE * MM_SCALE
# define MM_OFFSET_X 20
# define MM_OFFSET_Y 20
# define RAY_COLOR 0x29ab87
# define NUM_RAYS WIN_WIDTH
# define FOV 1.0471975512 // M_PI / 3
# define MM_VIEW_RANGE 5
# define GUN_NUM_SPRITES 5
# define HAND_SPRITES 11

typedef struct s_dda
{
	double		step_x;
	double		step_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		map_x;
	double		map_y;
	double		wall_dist;
	double		delta_dist_x;
	double		delta_dist_y;
	int			side;
}				t_dda;

typedef struct s_image
{
	void		*img_ptr;
	char		*pixel_data;
	int			bpp;
	int			endian;
	int			line_size;
	int			width;
	int			height;
	bool		has_green_screen;
}				t_image;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_player
{
	double		x;
	double		y;
	double		dx;
	double		dy;
	double		radius;
	double		angle;
	double		rotation_speed;
	double		move_speed;
	char		direction;
}				t_player;

typedef struct s_view
{
	int			start_row;
	int			end_row;
	int			start_col;
	int			end_col;
}				t_view;

typedef struct s_frame
{
	double		x;
	double		y;
	double		width;
	double		hieght;
}				t_frame;

typedef struct s_door
{
	double		progress;
	int			map_x;
	int			map_y;
	bool		is_opening;
	bool		is_closing;
	bool		is_horizontal;
}				t_door;

typedef struct s_texture
{
	double		hit_offset;
	double		first;
	double		last;
	double		x;
	double		y;
	double		pos;
	double		strip;
	t_dda		*ray;
	t_image		*img;
}				t_texture;

typedef struct s_data
{
	char		**map;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_image		*no;
	t_image		*so;
	t_image		*we;
	t_image		*ea;
	void		*mlx_ptr;
	void		*win_ptr;
	t_texture	*tex;
	t_image		*door_img;
	t_image		*wall_img;
	t_image		*buffer;
	t_image		**player_img;
	t_image		**hand_sprites;
	t_door		**doors;
	t_color		*floor;
	t_color		*ceiling;
	t_player	*player;
	t_view		view;
	t_frame		frame;
	int			map_height;
	int			map_width;
	int			exit_status;
	int			shoot_frame;
	int			hand_frame;
	int			doors_count;
	bool		is_shooting;
}				t_data;

// src
void			move_player(int key, t_data *data);
void			draw_sky(t_data *data, double max_to_fill, int x);
void			draw_floor(t_data *data, double floor_start, int x);
bool			is_wall(t_data *data, int x, int y);
void			player_rotation(int key, t_data *data);
void			field_of_view(t_data *data);
void			get_wall_distance(t_data *data, t_dda *ray, double angle);
int				mouse_rotate(int x, int y, t_data *data);
// utils
void			put_img_to_buffer(t_image *buffer_img, t_image *img, int x,
					int y);
void			get_player_pos(char **map, double *x, double *y,
					char *player_dir);
void			put_pixel_to_buffer(t_image *img, int x, int y, int color);
unsigned int	get_pixel_color(t_image *img, int x, int y);
void			put_error(char *msg, t_data *data, bool sys_error);
void			clear_buffer_img(t_image *buffer, int color);
void			load_textures(t_data *data);
void			init_buffer(t_data *data);
void			init_player(t_data *data);
void			init_doors(t_data *data);
bool			check_textures(char *line);
bool			is_line_empty(char *line);
bool			is_valid_char(char c);
bool			ft_isspace(char c);
bool			is_valid_key(int key);
int				skip_spacess(const char *str);
bool			is_door(t_data *data, int x, int y);
bool			is_door_close(t_data *data, int map_y, int map_x);
bool			is_door_blocking_ray(t_data *data, t_dda ray);
void			update_doors(t_data *data, t_door **doors);
void			hand_animation(t_image *buffer, t_image **hand_sprites,
					int hand_frame);
void			open_door(t_data *data, int plyr_x, int plyr_y);
t_door			*get_door_at(t_data *data, int map_x, int map_y);
unsigned int	get_rgb_color(int red, int green, int blue);
t_image			*get_tex_img(t_data *data, t_texture tex);
void			shoot(t_image *buffer, t_image **player_img, int shoot_frame);
// clean_exit
int				clean_exit(t_data *data);
// parsing
void			read_map(const char *map_path, int offset, t_data *data);
void			get_map_data(const char *map_path, t_data *data);
void			check_walls(char **map, t_data *data);
void			parse_map(t_data *data, char *av[]);
void			map_len(int fd, t_data *data);
// minimap
void			draw_minimap(char **map, t_data *data);
void			draw_frame(t_frame *frame, t_image *img, t_view view);
void			get_map_view_range(t_data *data);
int				my_bool(bool condition, int yes, int no);

#endif
