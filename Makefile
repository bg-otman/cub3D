PARSING = parsing/get_next_line/get_next_line.c parsing/get_next_line/get_next_line_utils.c parsing/parser.c \
parsing/get_map_data.c parsing/read_map.c
UTILS = utils/utils.c utils/init.c utils/helpers.c utils/put_pixels.c utils/clean_exit.c utils/doors.c \
utils/doors_utils.c
MINIMAP = minimap/draw_minimap.c minimap/minimap_frame.c
SRCS +=  main.c src/move_player.c src/ray_casting.c src/player_view.c $(PARSING) $(UTILS) $(MINIMAP)
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_LIB = mlx/libmlx_Linux.a -lX11 -lXext -lm
OBJS = $(SRCS:.c=.o)
INCLUDES = cub3d.h parsing/get_next_line/get_next_line.h
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LIBFT) -o $(NAME)

$(LIBFT) :
	@echo "processing ..."
	@$(MAKE) --no-print-directory -C libft
	@$(MAKE) --no-print-directory -C libft bonus

$(MLX_LIB) :
	@$(MAKE) --no-print-directory -C mlx

# bonus:

%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "cleaning..."
	@rm -f $(OBJS) get_next_line/*.o
	@$(MAKE) --no-print-directory -C libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C libft fclean

re: fclean all

.PHONY: clean all
