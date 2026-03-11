NAME = so_long
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SOURCES = main.c utils/ft_arrlen.c utils/ft_bzero.c utils/ft_check_map.c \
		  utils/ft_clean_exit.c utils/ft_clear_fd.c utils/ft_flood_fill.c \
		  utils/ft_fusion.c utils/ft_get_map.c utils/ft_handle.c \
		  utils/ft_init_cli.c utils/ft_init_window.c utils/ft_load_textures.c \
		  utils/ft_move_player.c utils/ft_perror.c utils/ft_pinfo.c \
		  utils/ft_psuccess.c utils/ft_putnbr_fd.c utils/ft_putstr_fd.c \
		  utils/ft_read.c utils/ft_render.c utils/ft_save_pos.c \
		  utils/ft_split.c utils/ft_strjoin.c utils/ft_strlen.c \
		  utils/ft_strncpy.c

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

CFLAGS = -Wall -Wextra -Werror -I includes/ -I $(MLX_DIR)
RM = rm -f
CC = cc
