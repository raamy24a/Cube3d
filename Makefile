# NAME = so_long

# SRC_FILES = srcs/render.c srcs/parsing.c srcs/main.c srcs/game.c \
# 	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
# 	printf/ft_printf.c printf/ft_putnbr.c srcs/cleanup.c \
# 	srcs/verify_extension_name.c srcs/parsingtwo.c srcs/ft_len_no_nl.c

# OBJ = $(SRC_FILES:.c=.o)

# CC = gcc
# CFLAGS = -g -Wall -Wextra -Werror
# INCLUDES = -Isrcs -Ilib -Ilibft
# LIBFT_DIR   = libft
# LIBFT       = $(LIBFT_DIR)/libft.a

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(OBJ)$(LIBFT) -Llib -lmlx -Llibft -lft -lXext -lX11 -lm -o $(NAME)

# srcs/%.o: srcs/%.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# get_next_line/%.o: get_next_line/%.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# clean:
# 	rm -f $(OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re



# **************************************************************************** #
#                                    CONFIG                                    #
# **************************************************************************** #

NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

LIBFT_DIR   = libft
MLX_DIR     = minilibx

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

INCLUDES    = -Iinclude -I$(LIBFT_DIR) -I$(MLX_DIR)

SRC_DIR     = src
OBJ_DIR     = obj

# ************************************************************************** #
#                             LISTE DES SOURCES                              #
# ************************************************************************** #

SRCS = \
	src/main.c \
	src/init.c \
	src/parsing/parse_map.c \
	src/parsing/parse_texture.c \
	src/render/render.c \
	src/render/raycast.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re