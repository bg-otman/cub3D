PARSING = parsing/get_next_line/get_next_line.c parsing/get_next_line/get_next_line_utils.c parsing/parser.c \
parsing/set_identifiers.c
UTILS = utils/utils.c utils/init.c utils/helpers.c
SRCS +=  main.c $(PARSING) $(UTILS)
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
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
