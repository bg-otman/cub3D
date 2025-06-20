PARSING = parsing/get_next_line/get_next_line.c parsing/get_next_line/get_next_line_utils.c parsing/parser.c \
parsing/get_map_data.c parsing/read_map.c
UTILS = utils/utils.c utils/init.c utils/helpers.c utils/put_pixels.c utils/clean_exit.c utils/doors.c \
utils/doors_utils.c
MINIMAP = minimap/draw_minimap.c minimap/minimap_frame.c
SRCS +=  src/move_player.c src/ray_casting.c src/player_view.c $(PARSING) $(UTILS) $(MINIMAP)
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_LIB = mlx/libmlx_Linux.a -lX11 -lXext -lm
OBJS = $(SRCS:.c=.o)
MANDATORY_OBJS = main.o $(OBJS)
BONUS_OBJS = main_bonus.o $(OBJS)
MANDATORY = /tmp/.mandatory_build
BONUS = /tmp/.bonus_build
INCLUDES = cub3d.h parsing/get_next_line/get_next_line.h
NAME = cub3D

all: $(MANDATORY)

$(MANDATORY): $(MANDATORY_OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(MLX_LIB) $(LIBFT) -o $(NAME)
	@touch $(MANDATORY)
	@rm -f $(BONUS)
	@echo "cub3D is ready 📦✅"
	@echo "\033[1;34m╔══════════════════════════════════════════════╗\033[0m"
	@echo "\033[1;34m║               \033[1;33mGAME CONTROLS\033[1;34m                  ║\033[0m"
	@echo "\033[1;34m╠══════════════════════════════════════════════╣\033[0m"
	@echo "\033[1;34m║  \033[1;37mMove:\033[0m W, A, S, D                            \033[1;34m║\033[0m"
	@echo "\033[1;34m║  \033[1;37mRotate:\033[0m ← → Arrows                          \033[1;34m║\033[0m"
	@echo "\033[1;34m║  \033[1;37mExit:\033[0m ESC                                   \033[1;34m║\033[0m"
	@echo "\033[1;34m╚══════════════════════════════════════════════╝\033[0m"

bonus: $(BONUS)

$(BONUS): $(BONUS_OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(MLX_LIB) $(LIBFT) -o $(NAME)
	@touch $(BONUS)
	@rm -f $(MANDATORY)
	@echo "cub3D bonus is ready 📦✅"
	@echo "\033[1;34m╔══════════════════════════════════════════════╗\033[0m"
	@echo "\033[1;34m║               \033[1;33mGAME CONTROLS\033[1;34m                  ║\033[0m"
	@echo "\033[1;34m╠══════════════════════════════════════════════╣\033[0m"
	@echo "\033[1;34m║  \033[1;37mMove:\033[0m W, A, S, D                            \033[1;34m║\033[0m"
	@echo "\033[1;34m║  \033[1;37mRotate:\033[0m ← → Arrows or Mouse                 \033[1;34m║\033[0m"
	@echo "\033[1;34m║  \033[1;37mShoot:\033[0m Enter                                \033[1;34m║\033[0m"
	@echo "\033[1;34m║  \033[1;37mDoors:\033[0m Spacebar to Open/Close               \033[1;34m║\033[0m"
	@echo "\033[1;34m║  \033[1;37mExit:\033[0m ESC                                   \033[1;34m║\033[0m"
	@echo "\033[1;34m╚══════════════════════════════════════════════╝\033[0m"


%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@echo "processing...🛠️"
	@$(MAKE) --no-print-directory -C libft
	@$(MAKE) --no-print-directory -C libft bonus

$(MLX_LIB) :
	@$(MAKE) --no-print-directory -C mlx

clean:
	@echo "cleaning...🛠️"
	@rm -f $(MANDATORY_OBJS) $(BONUS_OBJS) $(MANDATORY) $(BONUS)
	@$(MAKE) --no-print-directory -C libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C libft fclean

re: fclean all

.PHONY: clean all bonus